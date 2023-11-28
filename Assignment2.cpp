#include "galba.h"

void input()
{

}
constexpr float SQUARE_X_SPEED_PIXELS = 3.f;
constexpr int SQUARE_SIZE_PIXELS = 32;
constexpr int original_size = 32;
int current_size = original_size;
constexpr int original_radius = 32;
int radius = original_radius;
struct Square
{
    float x_position_in_pixels = 0.f;
    float x_facing_direction = 1.f;
    Color color;
};Square john = Square{};
struct Circle
{
    int center_x;
    int center_y;
    int radius;
    int x_speed;
    int y_speed;
    int num_bounces;
    Color color;
    bool color_swift;
};Circle leo = Circle{};
void game_init()
{
// INFO: Edit this code
    int window_width = get_window_width();
    john.x_position_in_pixels = window_width * 0.5f;
}
void circle_init()
{
    leo.center_x = round_to_int(get_window_width() * 0.5f);
    leo.center_y = round_to_int(get_window_height() * 0.5f);
    leo.radius = round_to_int(get_window_width() * 0.05f);
    leo.x_speed = 3;
    leo.y_speed = 2;
    leo.num_bounces = 0;
    leo.color = cyan;
    bool color_swift = false;
}
void update()
{
    int window_width = get_window_width();
// John will change its direction when pressing Space.
    if (is_key_pressed(Key::Space))
    {
        john.x_facing_direction = -john.x_facing_direction;
    }
    john.x_position_in_pixels += john.x_facing_direction *
                                 SQUARE_X_SPEED_PIXELS;
// John will change its direction when bouncing off the border.
    if (john.x_position_in_pixels < 0 || john.x_position_in_pixels +
                                         SQUARE_SIZE_PIXELS > window_width)
    {
        john.x_facing_direction = -john.x_facing_direction;
    }
// John will double its size when bouncing off the border.
    if (john.x_position_in_pixels == 657.f )
    {
        john.x_facing_direction = -john.x_facing_direction;
        current_size *= 2;
    }
// John will return to orginal size when bouncing off the border.
    if (john.x_position_in_pixels < 0)
    {
        current_size = 32;
    }
}
void update_circle()
{
    leo.center_x += leo.x_speed;
    leo.center_y += leo.y_speed;
    if (leo.center_x - leo.radius <= 0 || leo.center_x + leo.radius >=
                                          get_window_width())
    {
        leo.x_speed = -leo.x_speed;
// X-direction color changing mechanism
        leo.color_swift = true;
        if (leo.color_swift)
        {
            leo.color = Color{ static_cast<unsigned
            char>(random_int_in_range(0, 255)),
                               static_cast<unsigned char>(random_int_in_range(0, 255)),
                               static_cast<unsigned char>(random_int_in_range(0,
                                                                              255)),255 };
        }
        leo.color_swift = false;
// leo will double its size when bouncing off the border.
        leo.radius *= 2;
// To make sure that after doubing its radius still within the border
        if (leo.center_x + leo.radius >= get_window_width())
        {
            leo.center_x = get_window_width() - leo.radius;
        }
        else if (leo.center_x - leo.radius <= 0)
        {
            leo.center_x = leo.radius;
        }
    }
    if (leo.center_y - leo.radius <= 0 || leo.center_y + leo.radius >=
                                          get_window_height())
    {
        leo.y_speed = -leo.y_speed;
// Y-direction color changing mechanism
        leo.color_swift = true;
        if (leo.color_swift){
            leo.color = Color{static_cast<unsigned
            char>(random_int_in_range(0, 255)),
                              static_cast<unsigned char>(random_int_in_range(0, 255)),
                              static_cast<unsigned char>(random_int_in_range(0,
                                                                             255)),255 };
        }
        leo.color_swift = false;
// leo will return to orginal size when bouncing off the border
        leo.radius = 32;
// To make sure that after doubing its radius still within the border
        if (leo.center_y + leo.radius >= get_window_height())
        {
            leo.center_y = get_window_height() - leo.radius;
        }
        else if (leo.center_x - leo.radius <= 0)
        {
            leo.center_y = leo.radius;
        }
    }
// Setting restriction for the radius of leo
    if (leo.radius > get_window_width())
    {
        leo.radius = get_window_width() / 20;
    }
// Counting the times for bouncing the border
    if (leo.center_x + leo.radius >= get_window_width() || leo.center_x -
                                                           leo.radius <= 0 )
    {
        leo.num_bounces++;
    }else if( leo.center_y + leo.radius >= get_window_height() ||
              leo.center_y - leo.radius <= 0)
        leo.num_bounces++;
// When it bounces more than 12 times, it will vanish.
    if (leo.num_bounces >= 12)
    {
        leo.radius = 0;
    }
}
void render()
{
    int window_width = get_window_width();
    int window_height = get_window_height();
    int square_x = round_to_int(john.x_position_in_pixels);
    int square_y = round_to_int(window_height * 0.5f);
    john.color = Color{ static_cast<unsigned
    char>(random_int_in_range(0, 255)),
                        static_cast<unsigned char>(random_int_in_range(0, 255)),
                        static_cast<unsigned char>(random_int_in_range(0, 255)),255 };
    draw_rectangle(square_x, square_y, current_size, current_size,
                   john.color);
}
void circle_render()
{
    draw_circle(leo.center_x, leo.center_y, leo.radius, leo.color);
}
int main(int argc, char** argv)
{
    initialize(720, 720, "Window");
    game_init();
    circle_init();
    while (is_window_open())
    {
        update();
        update_circle();
        clear_window();
        render();
        circle_render();
        display();
    }
    return 0;
}
