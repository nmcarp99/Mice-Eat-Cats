#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

using namespace std;
const float FPS = 60;
ALLEGRO_BITMAP * bckground = NULL;
ALLEGRO_BITMAP * mouse = NULL;
ALLEGRO_BITMAP * playpic = NULL;
ALLEGRO_BITMAP * optionspic = NULL;
ALLEGRO_BITMAP * creditspic = NULL;
ALLEGRO_BITMAP * exitpic = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
float mouseX = -550;
bool endProcess = false;
bool mouse_button_1 = false;
char selection = ' ';

int closeDisplay()
{
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(bckground);
	al_destroy_bitmap(mouse);

	return 0;
}

int redrawStartUp()
{
	//draw here
	al_draw_bitmap(bckground, 0, 0, 0);
	al_draw_bitmap(mouse, mouseX, 532, 0);
	al_flip_display();
	return 0;
}

int redrawMenu()
{
	al_clear_to_color(al_map_rgb(171, 205, 239));
	//draw here
	al_draw_filled_rounded_rectangle(440, 125, 640, 200, 20, 30, al_map_rgb(0, 128, 0));
	al_draw_bitmap(playpic, 465, 125, 0);
	al_draw_filled_rounded_rectangle(440, 225, 640, 300, 20, 30, al_map_rgb(0, 128, 0));
	al_draw_bitmap(optionspic, 465, 225, 0);
	al_draw_filled_rounded_rectangle(440, 325, 640, 400, 20, 30, al_map_rgb(0, 128, 0));
	al_draw_bitmap(creditspic, 465, 325, 0);
	al_draw_filled_rounded_rectangle(440, 425, 640, 500, 20, 30, al_map_rgb(0, 128, 0));
	al_draw_bitmap(exitpic, 465, 425, 0);
	al_flip_display();
	return 0;
}

int redrawGame()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	//draw here
	al_flip_display();
	return 0;
}

int play()
{
	bool inGame = true;

	while (inGame) {
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		ALLEGRO_MOUSE_STATE state;

		// Intalize timeout
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

		if (get_event) {
			switch (event.type) {
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					inGame = false;
					endProcess = true;
					break;
				case ALLEGRO_EVENT_TIMER:
					redrawGame();
					break;
			}
		}
	}

	return 0;
}

int options()
{
	cout<<"options"<<endl;
	return 0;
}

int credits()
{
	cout<<"credits"<<endl;
	return 0;
}

int checkSelection()
{
	switch (selection) {
		case 'p':
			play();
			break;
		case 'o':
			options();
			break;
		case 'c':
			credits();
			break;
	}
	return 0;
}

int menu()
{
	while (!endProcess) {
		al_install_mouse();

		bool mouse_button_1 = false;

		bool inMenu = true;

		while (inMenu) {
			ALLEGRO_EVENT event;
			ALLEGRO_TIMEOUT timeout;
			ALLEGRO_MOUSE_STATE state;

			// Intalize timeout
			al_init_timeout(&timeout, 0.06);

			// Get state of mouse
			al_get_mouse_state(&state);

			bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

			if (mouse_button_1 == false) {
				if (state.buttons & 1) {
					mouse_button_1 = true;
				}
			}
			else {
				if (!(state.buttons & 1)) {
					if (state.x >= 440 && state.x <= 640) {
						if (state.y >= 125 && state.y <= 200) {
							selection = 'p';
							inMenu = false;
						}
						if (state.y >= 225 && state.y <= 300) {
							selection = 'o';
							inMenu = false;
						}
						if (state.y >= 325 && state.y <= 400) {
							selection = 'c';
							inMenu = false;
						}
						if (state.y >= 425 && state.y <= 500) {
							selection = 'e';
							endProcess = true;
							inMenu = false;
						}
					}
					mouse_button_1 = false;
				}
			}

			if (get_event) {
				switch (event.type) {
					case ALLEGRO_EVENT_DISPLAY_CLOSE:
						inMenu = false;
						endProcess = true;
						break;
					case ALLEGRO_EVENT_TIMER:
						redrawMenu();
						break;
				}
			}
		}

		al_uninstall_mouse();

		checkSelection();
	}
	return 0;
}

int main(int argc, char *argv[])
{
	bool startupDone = false;
	bool paused = false;

	// Initializations and setup
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	display = al_create_display(1080, 640);
	al_set_window_title(display, "I Topi Mangiano Gatti");
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0/FPS);
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	// Load images
	mouse = al_load_bitmap("mouse.png");
	bckground = al_load_bitmap("bckground.jpeg");
	playpic = al_load_bitmap("play.png");
	optionspic = al_load_bitmap("options.png");
	creditspic = al_load_bitmap("credits.png");
	exitpic = al_load_bitmap("exit.png");

	// Clear screen to black
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	// Game Loop
	while (!startupDone) {
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;

		// Intalize timeout
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);
		mouseX = mouseX + 6;
		if (get_event) {
			switch (event.type) {
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					return 0;
					break;
				case ALLEGRO_EVENT_TIMER:
					redrawStartUp();
					break;
			}
		}
		if (mouseX >= 1080) {
			startupDone = true;
			al_rest(1);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_flip_display();
			al_rest(1);
		}
	}

	menu();

	closeDisplay();

	return 0;
}
