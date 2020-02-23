#include <string>
#include <fstream>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

using namespace std;
const float FPS = 60;
ALLEGRO_BITMAP * bckground = NULL;
ALLEGRO_BITMAP * mouse = NULL;
ALLEGRO_BITMAP * creditsbck = NULL;
ALLEGRO_BITMAP * menubck = NULL;
ALLEGRO_BITMAP * optionsybck = NULL;
ALLEGRO_BITMAP * optionsxbck = NULL;
ALLEGRO_BITMAP * smallmouse = NULL;
ALLEGRO_BITMAP * smallmouse1 = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
int mouseFrames = 0;
bool mouse1 = false;
float mouseX = -550;
float mouseY = 0;
bool endProcess = false;
bool mouse_button_1 = false;
bool key_left = false;
bool key_right = false;
bool key_up = false;
bool key_down = false;
bool key_esc = false;
bool optionsx = false;
char selection = ' ';

bool checkSound() {
	fstream openfile("sound.txt", fstream::in);
	string text;
	openfile>>text;
	openfile.close();
	if (text == "0") {
		optionsx = true;
		return 0;
	}
	else if (text == "1") {
		optionsx = false;
		return 0;
	}
	return 0;
}

int changeSound() {
	fstream openfile("sound.txt", fstream::in);
	string text;
	openfile>>text;
	openfile.close();
	fstream file("sound.txt", fstream::out);
	if (text == "1") {
		file<<"0";
		optionsx = true;
		return 0;
	}
	else if (text == "0") {
		file<<"1";
		optionsx = false;
		return 0;
	}
	file.close();
	return 0;
}

int closeDisplay()
{
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(bckground);
	al_destroy_bitmap(creditsbck);
	al_destroy_bitmap(optionsybck);
	al_destroy_bitmap(optionsxbck);
	al_destroy_bitmap(smallmouse);
	al_destroy_bitmap(smallmouse1);
	al_destroy_bitmap(menubck);
	al_destroy_bitmap(mouse);

	return 0;
}

int drawCredits()
{
	al_draw_bitmap(creditsbck, 0, 0, 0);
	//draw here
	al_flip_display();
	return 0;
}

int drawOptions()
{
	if (!optionsx) {
		al_draw_bitmap(optionsybck, 0, 0, 0);
	}
	else {
		al_draw_bitmap(optionsxbck, 0, 0, 0);
	}
	//draw here
	al_flip_display();
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
	al_draw_bitmap(menubck, 0, 0, 0);
	//draw here
	al_flip_display();
	return 0;
}

int redrawGame()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	//draw here
	if (!mouse1) {
		al_draw_bitmap(smallmouse, mouseX, mouseY, 0);
	}
	else {
		al_draw_bitmap(smallmouse1, mouseX, mouseY, 0);
	}
	al_flip_display();
	return 0;
}

bool checkDown(ALLEGRO_KEYBOARD_STATE state)
{
	if (al_key_down(&state, ALLEGRO_KEY_DOWN)) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool checkUp(ALLEGRO_KEYBOARD_STATE state)
{
	if (al_key_down(&state, ALLEGRO_KEY_UP)) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool checkRight(ALLEGRO_KEYBOARD_STATE state)
{
	if (al_key_down(&state, ALLEGRO_KEY_RIGHT)) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool checkLeft(ALLEGRO_KEYBOARD_STATE state)
{
	if (al_key_down(&state, ALLEGRO_KEY_LEFT)) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool checkEsc(ALLEGRO_KEYBOARD_STATE state)
{
	if (key_esc == false) {
		if (al_key_down(&state, ALLEGRO_KEY_ESCAPE)) {
			key_esc = true;
			return false;
		}
	}
	else {
		if (!(al_key_down(&state, ALLEGRO_KEY_ESCAPE))) {
			key_esc = false;
			return true;
		}
	}
	return false;
}

int play()
{
	al_install_keyboard();

	mouseFrames = 0;
	mouse1 = false;
	mouseX = 0;
	mouseY = 0;

	bool inGame = true;

	while (inGame) {
		ALLEGRO_KEYBOARD_STATE state;
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;

		bool frameUp = false;

		al_get_keyboard_state(&state);

		// Intalize timeout
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

		if (((mouseFrames + 2) % 10) == 0) {
			mouse1 = !mouse1;
		}

		if (checkEsc(state)) {
			inGame = false;
		}

		if (checkLeft(state)) {
			mouseX = mouseX - 10;
			if (!frameUp) {
				mouseFrames = mouseFrames + 1;
				frameUp = true;
			}
		}
		if (checkUp(state)) {
			mouseY = mouseY - 10;
			if (!frameUp) {
				mouseFrames = mouseFrames + 1;
				frameUp = true;
			}
		}
		if (checkDown(state)) {
			mouseY = mouseY + 10;
			if (!frameUp) {
				mouseFrames = mouseFrames + 1;
				frameUp = true;
			}
		}
		if (checkRight(state)) {
			mouseX = mouseX + 10;
			if (!frameUp) {
				mouseFrames = mouseFrames + 1;
				frameUp = true;
			}
		}

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

	al_uninstall_keyboard();

	return 0;
}

int credits()
{
	al_install_mouse();

	bool inCredits = true;

	bool mouse_button_1 = false;

	drawCredits();

	while (inCredits) {
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		ALLEGRO_MOUSE_STATE state;

		// Intalize timeout
		al_init_timeout(&timeout, 0.06);

		//get mouse state
		al_get_mouse_state(&state);

		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

		if (mouse_button_1 == false) {
			if (state.buttons & 1) {
				mouse_button_1 = true;
			}
		}
		else {
			if (!(state.buttons & 1)) {
				inCredits = false;
				mouse_button_1 = false;
			}
		}

		if (get_event) {
			switch (event.type) {
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					inCredits = false;
					endProcess = true;
					break;
			}
		}
	}

	al_uninstall_mouse();

	return 0;
}

int options()
{
	al_install_mouse();

	bool inOptions = true;

	bool mouse_button_1 = false;


	while (inOptions) {
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		ALLEGRO_MOUSE_STATE state;

		// Intalize timeout
		al_init_timeout(&timeout, 0.06);

		//get mouse state
		al_get_mouse_state(&state);

		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

		if (mouse_button_1 == false) {
			if (state.buttons & 1) {
				mouse_button_1 = true;
			}
		}
		else {
			if (!(state.buttons & 1)) {
				if (state.x >= 90 && state.x <= 990 && state.y >= 256 && state.y <= 346) {
					changeSound();
				}
				else {
					inOptions = false;
				}
				mouse_button_1 = false;
			}
		}

		if (get_event) {
			switch (event.type) {
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					inOptions = false;
					endProcess = true;
					break;
				case ALLEGRO_EVENT_TIMER:
					drawOptions();
					break;

			}
		}
	}

	al_uninstall_mouse();

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
						selection = 'e';
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
	checkSound();

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
	creditsbck = al_load_bitmap("creditsbck.png");
	optionsybck = al_load_bitmap("optionsybck.png");
	optionsxbck = al_load_bitmap("optionsxbck.png");
	mouse = al_load_bitmap("mouse.png");
	smallmouse = al_load_bitmap("smallmouse.png");
	smallmouse1 = al_load_bitmap("smallmouse1.png");
	bckground = al_load_bitmap("bckground.jpeg");
	menubck = al_load_bitmap("menubck.png");

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
