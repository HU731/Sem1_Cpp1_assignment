#include <ctime>
#include <string>
#include <vector>
#include "galba.h"
enum class GameMode
{
    Menu,
    Easy,
    Medium,
    Hard
};
const int MolesNum = 10;
#define DEF_MENU_STATE 0 // Using macro to instead choice 0 and 1 in switch-case
#define DEF_MOUSE_STATE 1
int int_state = DEF_MENU_STATE;
int MoleSpawntime = 2;
struct Position
{
    int x;
    int y;
};
struct Mole
{
    Position position;
    int radius;
    bool visible;
    bool visibletime;
};
int score = 0;
int timeLimit = 0;
float timer = 0.0f;
GameMode gameState = GameMode::Menu;
std::vector<Mole> moles;
void Game_reset()
{
    score = 0;
    timer = 0.0f;
    moles.clear(); // Clear the items in std::vector
    for (int i = 0; i < MolesNum; ++i)
    {
        Mole newMole;
        newMole.position.x = random_int_in_range(0, get_window_width() - 70);
        newMole.position.y = random_int_in_range(0, get_window_height() - 70);
        newMole.radius = 30;
        newMole.visible = true;
        moles.push_back(newMole); // Put some circles into std::vector template
    }
    //std::this_thread::sleep_for(std::chrono::seconds(MoleSpawntime));
    //newMole.visibletime = random_float_in_range(1.0f, 3.0f);
}
void GameModeChoice()
{
    if (gameState == GameMode::Menu)
    {
        {
            // draw three rectangles corresponding to three levels
            draw_rectangle(250, 100, 200, 100, green); // Easy
            draw_text(270, 120, white, "Easy");
            draw_rectangle(250, 250, 200, 100, yellow); // Medium
            draw_text(270, 270, white, "Medium");
            draw_rectangle(250, 400, 200, 100, red); // Hard
            draw_text(270, 420, white, "Hard");
            display();
            int mouseX = get_mouse_x();
            int mouseY = get_mouse_y();
            if (is_button_pressed(Button::Left))
            {
                // To check if the mouth is over the menu rectangles
                if (mouseX >= 250 && mouseX <= 450)
                {
                    if (mouseY >= 100 && mouseY <= 200)
                    {
                        timeLimit = 13; // Easy 13sec
                        Game_reset();
                        int_state = DEF_MOUSE_STATE;
                    }
                    else if (mouseY >= 250 && mouseY <= 350)
                    {
                        timeLimit = 9; // Medium 9sec
                        Game_reset();
                        int_state = DEF_MOUSE_STATE;
                    }
                    else if (mouseY >= 400 && mouseY <= 500)
                    {
                        timeLimit = 6; // Hard 6sec
                        Game_reset();
                        int_state = DEF_MOUSE_STATE;
                    }
                }
            }
        }
    }
}
void ModeChoiceAgain()
{
    if (timer >= timeLimit)
    {
        gameState = GameMode::Menu;
    }
}
bool is_mouth_over_moles(Position mouse_position, Mole item)
{
    double distance = sqrt(pow(mouse_position.x - item.position.x, 2)
                           + pow(mouse_position.y - item.position.y, 2));
    if (distance <= item.radius) { return true; }
    else { return false; }
}
void WhackMole()
{
    for (int i = 0; i < moles.size(); ++i)
    {
        if (moles[i].visible)
        {
            if (i > 0 && i <= 2){
                if (timer > 1.0f && timer <= 3.0f){
                    moles[i].visibletime = false;
                }else{
                    moles[i].visibletime = true;
                }
            }else if (i > 2 && i <= 4){
                if (timer > 8.0f && timer <= 12.0f){
                    moles[i].visibletime = false;
                }else{
                    moles[i].visibletime = true;
                }
            }else if (i > 4 && i <= 6){
                if (timer > 5.0f && timer <= 8.0f){
                    moles[i].visibletime = false;
                }else{
                    moles[i].visibletime = true;
                }
            }else if (i > 6 && i <= 8){
                if (timer > 4.0f && timer <= 7.0f){
                    moles[i].visibletime = false;
                }else{
                    moles[i].visibletime = true;
                }
            }else if (i > 8 && i <= 10){
                if (timer >= 2.0f && timer < 4.0f)
                {
                    moles[i].visibletime = false;
                }else{
                    moles[i].visibletime = true;
                }
            }
            if(moles[i].visibletime)
            {
                draw_circle(moles[i].position.x, moles[i].position.y, moles[i].radius,
                            magenta);
            }
            if (is_button_pressed(Button::Left))
            {
                int mouseX = get_mouse_x();
                int mouseY = get_mouse_y();
                Position mouse_position = { mouseX,mouseY };
                if (is_mouth_over_moles(mouse_position, moles[i]))
                {
                    moles[i].visible = false;
                    score += 1;
                }
            }
        }
    }
}
void board_render()
{
    draw_text(10, 10, white, "Score: " + std::to_string(score));
    draw_text(10, 30, white, "Time: " + std::to_string(static_cast<int>(timeLimit -
                                                                        timer)));
    //Using to_string function from string standard library,
    // which is used to transfer different data type to string type.
}
int main(int argc, char** argv)
{
    initialize(800, 600, "Whack a Mole");
    while (is_window_open())
    {
        clear_window();
        switch (int_state)
        {
            case DEF_MENU_STATE:
            {
                GameModeChoice();
                break;
            }
            case DEF_MOUSE_STATE:
            {
                WhackMole();
                timer += 1.0f / 60.0f;
                board_render();
                display();
                if (timeLimit - timer <= 0.0f)
                {
                    int_state = DEF_MENU_STATE;
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
};
