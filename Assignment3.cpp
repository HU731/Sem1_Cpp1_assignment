#include "galba.h"
#include <vector>
constexpr int CIRCLE_RADIUS = 16;
struct Position {
    float x;
    float y;
};
struct Circle {
    int radius;
    Position position;
    Color color;
};
Circle mario = Circle{ 16, 0, 0, white };
std::vector<Circle> marios;
Color random_color()
{
    return mario.color = Color{ static_cast<unsigned char>(random_int_in_range(0,
                                                                               255)),
                                static_cast<unsigned char>(random_int_in_range(0, 255)),
                                static_cast<unsigned char>(random_int_in_range(0, 255)),255 };
}
bool is_mouth_over_circle(Position mouse_position, Circle circle)
{
    double distance = sqrt(pow(mouse_position.x - circle.position.x, 2)
                           + pow(mouse_position.y - circle.position.y, 2));
    if (distance <= CIRCLE_RADIUS) { return true;}
    else { return false; }
}
void update()
{
    Circle Mario_next;
    Position mouse_Position;
    mouse_Position.x = static_cast<float>(get_mouse_x());
    mouse_Position.y = static_cast<float>(get_mouse_y());
    if (is_button_pressed(Button::Right))
    {
        if (marios.size() == 0)
        {
            Mario_next.position.x = static_cast<float>(get_mouse_x());
            Mario_next.position.y = static_cast<float>(get_mouse_y());
            Mario_next.color = random_color();
            marios.push_back(Mario_next);
            return;
        }
        for (auto it = marios.begin(); it != marios.end(); it++)
        {
            if (is_mouth_over_circle(mouse_Position, *it))
            {
                marios.erase(it);
                break;
            }
            else {
                if (marios.size() < 12)
                {
                    Mario_next.position.x =
                            static_cast<float>(get_mouse_x());
                    Mario_next.position.y =
                            static_cast<float>(get_mouse_y());
                    Mario_next.color = random_color();
                    marios.push_back(Mario_next);
                    return;
                }
            }
        }
    }
    if (is_button_pressed(Button::Left))
    {
        for (Circle& circle : marios)
        {
            if (is_mouth_over_circle(mouse_Position, circle))
            {
                circle.color = random_color();
            }
        }
    }
}
void render()
{
    for (const Circle& circle : marios)
    {
        draw_circle(round_to_int(circle.position.x),
                    round_to_int(circle.position.y), CIRCLE_RADIUS, circle.color);
    }
}
int main(int argc, char** argv)
{
    initialize(720, 720, "Window");
    while (is_window_open())
    {
        update();
        clear_window();
        render();
        display();
    }
    return 0;
}