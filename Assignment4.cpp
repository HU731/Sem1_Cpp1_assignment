#include "galba.h"
#include <vector>
#include <list>
#include <cmath>
constexpr float PI = 3.1415926535f;
struct Vector2
{
    float x;
    float y;
};
// Calculate distance between two points
float distance(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}
// Random direction function
Vector2 random_direction()
{
    float angle = random_float_01() * 2 * PI;
    float speed = 5.0f;
    return Vector2{ cosf(angle) * speed, sinf(angle) * speed };
}
class Entity
{
public:
    Vector2 position = {};
    bool dead = false;
    virtual void update() = 0;
    virtual void render() = 0;
};
// Goat class
class Goat : public Entity
{
private:
    int bushesEaten = 0;
public:
    float size = 35.0f;// Initialize to 10
    std::vector<Entity*> all_entities = {};
    void update() override
    {
        // Goats move in a random direction
        Vector2 dir = random_direction();
        position.x += dir.x;
        position.y += dir.y;
        // Bounce on the edges of the window
        if (position.x < 0 || position.x > 1280) {
            position.x = std::max(0.0f, std::min(position.x, 1280.0f));
        }
        if (position.y < 0 || position.y > 720) {
            position.y = std::max(0.0f, std::min(position.y, 720.0f));
        }
    }
    void render() override
    {
        // Rendering Goat
        draw_circle(round_to_int(position.x), round_to_int(position.y),
                    round_to_int(size), white);
    }
    void eatBush() {
        bushesEaten++;
        size += 10.0f;
        if (bushesEaten >= 3)
        {
            dead = true; // Goats will die after eating 3 bushes
        }
    }
};
// Bush class
class Bush : public Entity {
private:
    int growth = 0;
    bool eaten = false;
public: float radius = 10.0f;// Initialize radius to 10
    void update() override
    {
        if (!eaten && growth < 600)
        {
            // Bushes_radius growing from 10 to 20
            radius += 0.01f;
            growth++;
        }
    }
    void render() override
    {
        if (!eaten)
        { // Rendering bushes
            draw_circle(round_to_int(position.x), round_to_int(position.y),
                        round_to_int(radius), green);
        }
    }
    int getGrowth() const
    {
        return growth;
    }
    bool isEaten() const
    {
        return eaten;
    }
};
class Level
{
private:
    std::list<Goat> all_goats = {};
    std::list<Bush> all_bushes = {};
    std::vector<Entity*> all_entities = {};
public:
    void add_entity(const Goat& goat)
    {
        all_goats.push_back(goat);
        all_entities.push_back(&all_goats.back());
    }
    void add_entity(const Bush& bush)
    {
        all_bushes.push_back(bush);
        all_entities.push_back(&all_bushes.back());
    }
    void remove_all_dead_entities()
    {
        auto new_last_entity = std::remove_if
                (all_entities.begin(), all_entities.end(),[](const Entity* e) -> bool
                {return e->dead; });
        all_entities.erase(new_last_entity, all_entities.end());
        all_goats.remove_if([](const Goat& g) -> bool { return g.dead; });
    }
    void init()
    {
        // TODO: Implement
    }
    void update()
    {
        if (is_button_pressed(Button::Right))
        {
            // Spawn a goat
            Goat goat;
            goat.position.x = static_cast<float>(get_mouse_x());
            goat.position.y = static_cast<float>(get_mouse_y());
            add_entity(goat);
        }
        if (is_button_pressed(Button::Left))
        {
            // Spawn a bush
            Bush bush;
            bush.position.x = static_cast<float>(get_mouse_x());
            bush.position.y = static_cast<float>(get_mouse_y());
            add_entity(bush);
        }
        for (Entity* entity : all_entities)
        {
            entity->update();

            remove_all_dead_entities();
        }
        for (Goat& goat : all_goats)
        {
            if (!goat.dead)
            {
                for (Bush& bush : all_bushes)
                {
                    if (!bush.dead)
                    {
                        float dist = distance(goat.position.x, goat.position.y,
                                              bush.position.x, bush.position.y);
                        if (dist < (goat.size + bush.radius) / 2)
                        {
                            goat.eatBush();
                            bush.dead = true;
                        }
                    }
                }
            }
        }
    }
    void render()
    {
        // Implement rendering
        for (Entity* entity : all_entities)
        {
            entity->render();
        }
    }
};
int main(int argc, char** arg)
{
    Level level;
    initialize(1280, 720, "Window");
    level.init();
    while (is_window_open())
    {
        level.update();
        clear_window();
        level.render();
        display();
    }
    return 0;
};
