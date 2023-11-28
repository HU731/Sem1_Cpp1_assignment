#include "galba.h"

/* 
	Instructions:

	Edit the content of the render() function.

	DO NOT add nor edit any code in the main() function, except where you have permission to do so.
*/


void input()
{
	// INFO: You should't need to put code here but you can do it if you wish.
}

void render()
{
	// INFO: Edit this code

	int window_width  = get_window_width();
	int window_height = get_window_height();

	int circle_radius = round_to_int(fminf(window_width * 0.1f, window_height * 0.1f));

	int circle_center_x = round_to_int(window_width * 0.5f);
	int circle_center_y = round_to_int(window_height * 0.5f);
	draw_circle(circle_center_x, circle_center_y, circle_radius);
}

int main(int argc, char** argv)
{
	initialize(720, 720, "Window");

	// Add code here (before the while-loop) if it only needs to run once at the beginning.

	while (is_window_open())
	{
		input();

		clear_window();
		render();
		display();
	}

	return 0;
}