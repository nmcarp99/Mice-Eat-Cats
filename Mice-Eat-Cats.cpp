#include <fstream>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

using namespace std;
const float FPS = 60;
ALLEGRO_BITMAP* houndproductions = NULL;
ALLEGRO_BITMAP* itopimangianogatti = NULL;
ALLEGRO_BITMAP* levelBackground[2];
ALLEGRO_BITMAP* wanderingrangerstudios = NULL;
ALLEGRO_BITMAP* upmouse = NULL;
ALLEGRO_BITMAP* foot = NULL;
ALLEGRO_BITMAP* bckground = NULL;
ALLEGRO_BITMAP* mouse = NULL;
ALLEGRO_BITMAP* creditsbck = NULL;
ALLEGRO_BITMAP* menubck = NULL;
ALLEGRO_BITMAP* optionsybck = NULL;
ALLEGRO_BITMAP* optionsxbck = NULL;
ALLEGRO_BITMAP* smallmouse = NULL;
ALLEGRO_BITMAP* smallmouse1 = NULL;
ALLEGRO_BITMAP* backsmallmouse = NULL;
ALLEGRO_BITMAP* backsmallmouse1 = NULL;
ALLEGRO_BITMAP* finish = NULL;
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE_INSTANCE* backgroundMusicInstance = NULL;
ALLEGRO_SAMPLE* backgroundMusic = NULL;
ALLEGRO_SAMPLE_INSTANCE* gameMusicInstance = NULL;
ALLEGRO_SAMPLE* gameMusic = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;
int levelOneMapHor[] = {
	100, 400
};
int levelOneMapVer[] = {
	51, 211
};
int level = 0;
int numSamples = 1;
int mouseFrames = 0;
int levelProgress = 0;
int numbackgroundPassed = 0;
bool mouse1 = false;
float mouseX = -550;
float mouseY = 0;
float targetMouseY = 0;
float backgroundX = 0;
float footY = 640;
bool inGame = true;
bool waitingFoot = true;
bool endProcess = false;
bool mouse_button_1 = false;
bool key_left = true;
bool key_right = true;
bool key_up = false;
bool key_down = false;
bool key_esc = false;
bool optionsx = false;
char selection = ' ';
char mouseDir = 'f';

int redrawFade(ALLEGRO_BITMAP* image, float fadeTransparency)
{
	al_draw_bitmap(image, 0, 0, 0);
	al_draw_filled_rectangle(0, 0, 1080, 640, al_map_rgba_f(0, 0, 0, fadeTransparency));
	//draw here
	al_flip_display();
	return 0;
}

int fade(ALLEGRO_BITMAP* image, int framesUpTo312, bool trueForOutFalseForIn, int totalLength)
{
	int frames = 0;
	float fadeTransparency = 0.0f;
	if (trueForOutFalseForIn == false) {
		fadeTransparency = 1.0f;
	}
	for (frames = 0; frames < totalLength; ++frames) {
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;

		// Intalize timeout
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

		if (get_event) {
			switch (event.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				endProcess = true;
				return 0;
				break;
			case ALLEGRO_EVENT_TIMER:
				redrawFade(image, fadeTransparency);
				if (frames >= framesUpTo312) {
					if (trueForOutFalseForIn == true) {
						fadeTransparency += 0.025641;
					}
					else {
						fadeTransparency -= 0.025641;
					}
				}
				break;
			}
		}
	}

	return 0;
}

int easterFoot()
{
	smallmouse = al_load_bitmap("rat.png");
	smallmouse1 = al_load_bitmap("rat1.png");
	backsmallmouse = al_load_bitmap("backrat.png");
	backsmallmouse1 = al_load_bitmap("backrat1.png");
	return 0;
}

int check_for_restart_thememusic()
{
	if (!al_get_sample_instance_playing(backgroundMusicInstance) && !optionsx) {
		al_play_sample_instance(backgroundMusicInstance);
	}
	return 0;
}

int check_for_restart_gamemusic()
{
	if (!al_get_sample_instance_playing(gameMusicInstance) && !optionsx) {
		al_play_sample_instance(gameMusicInstance);
	}
	return 0;
}

bool checkLevel()
{
	fstream openfile("level.txt", fstream::in);
	int text;
	openfile>>text;
	openfile.close();
	level = text;
	return 0;
}

int changeLevel()
{
	fstream file("level.txt", fstream::out);
	file<<level;
	file.close();

	return 0;
}

bool checkSound()
{
	fstream openfile("sound.txt", fstream::in);
	char text;
	openfile >> text;
	openfile.close();
	if (text == '0') {
		optionsx = true;
		return 0;
	}
	else {
		optionsx = false;
		return 0;
	}
	return 0;
}

int changeSound()
{
	fstream openfile("sound.txt", fstream::in);
	char text;
	openfile >> text;
	openfile.close();
	fstream file("sound.txt", fstream::out);
	if (text == '0') {
		file << "1";
		optionsx = false;
		return 0;
	}
	else {
		file << "0";
		al_stop_sample_instance(backgroundMusicInstance);
		optionsx = true;
		return 0;
	}
	file.close();
	return 0;
}

int closeDisplay()
{
	al_destroy_display(display);
	al_destroy_bitmap(wanderingrangerstudios);
	al_destroy_bitmap(itopimangianogatti);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(finish);
	al_destroy_bitmap(houndproductions);
	al_destroy_bitmap(levelBackground[0]);
	al_destroy_bitmap(levelBackground[1]);
	al_destroy_bitmap(foot);
	al_destroy_bitmap(creditsbck);
	al_destroy_bitmap(optionsybck);
	al_destroy_bitmap(optionsxbck);
	al_destroy_bitmap(mouse);
	al_destroy_bitmap(smallmouse);
	al_destroy_bitmap(smallmouse1);
	al_destroy_bitmap(backsmallmouse);
	al_destroy_bitmap(backsmallmouse1);
	al_destroy_bitmap(upmouse);
	al_destroy_bitmap(bckground);
	al_destroy_bitmap(menubck);
	al_destroy_sample(backgroundMusic);
	al_destroy_sample_instance(backgroundMusicInstance);

	return 0;
}

int drawCredits()
{
	al_draw_bitmap(creditsbck, 0, 0, 0);
	//draw here
	if (waitingFoot == false) {
		al_draw_bitmap(foot, 0, footY, 0);
		if (footY > 507) {
			footY = footY - 1;
		}
	}
	al_flip_display();
	return 0;
}

int drawOptions()
{
	//draw here
	if (!optionsx) {
		al_draw_bitmap(optionsybck, 0, 0, 0);
	}
	else {
		al_draw_bitmap(optionsxbck, 0, 0, 0);
	}
	if (waitingFoot == false) {
		al_draw_bitmap(foot, 0, footY, 0);
		if (footY > 507) {
			footY = footY - 1;
		}
	}
	al_flip_display();
	return 0;
}

int drawLevelEnd()
{
	al_draw_bitmap(optionsybck, 0, 0, 0);
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
	if (waitingFoot == false) {
		al_draw_bitmap(foot, 0, footY, 0);
		if (footY > 507) {
			footY = footY - 1;
		}
	}
	al_flip_display();
	return 0;
}

int levelEnd()
{
	bool inLevelEnd = true;

	bool mouse_button_1 = false;

	levelProgress = 0;
	backgroundX = 0;
	mouseFrames = 0;
	mouse1 = false;
	mouseX = 300;
	targetMouseY = 51;
	mouseY = 51;

	while (inLevelEnd) {
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
					inLevelEnd = false;
				}
				mouse_button_1 = false;
			}
		}

		if (get_event) {
			switch (event.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				inLevelEnd = false;
				endProcess = true;
				break;
			case ALLEGRO_EVENT_TIMER:
				drawLevelEnd();
				break;

			}
		}
	}

	changeLevel();

	return 0;
}

int redrawGame()
{
	switch (mouseDir) {
		case 'f':
			if (backgroundX <= (0 - 1080)) {
				backgroundX = 0;
				numbackgroundPassed = numbackgroundPassed + 1;
			}
			break;
		case 'b':
			if (backgroundX >= 0) {
				backgroundX = (0 - 1080);
				numbackgroundPassed = numbackgroundPassed - 1;
			}
			break;
	}
	al_draw_bitmap(levelBackground[level], backgroundX, 0, 0);
	if (backgroundX <= -1) {
		al_draw_bitmap(levelBackground[level], backgroundX + 1080, 0, 0);
	}
	else if (backgroundX >= 1080) {
		al_draw_bitmap(levelBackground[level], 1080 - backgroundX, 0, 0);
	}
	if (numbackgroundPassed >= 3) {
		al_draw_bitmap(finish, backgroundX + 1080, 0, 0);
		if (backgroundX <= -720) {
			numbackgroundPassed = 0;
			++level;
			levelEnd();
		}
	}

	//draw here
	if (targetMouseY != mouseY) {
		al_draw_bitmap(upmouse, mouseX, mouseY, 0);
	}
	else {
		switch (mouseDir) {
			case 'f':
				if (!mouse1) {
					al_draw_bitmap(smallmouse, mouseX, mouseY, 0);
				}
				else {
					al_draw_bitmap(smallmouse1, mouseX, mouseY, 0);
				}
				break;
			case 'b':
				if (!mouse1) {
					al_draw_bitmap(backsmallmouse, mouseX, mouseY, 0);
				}
				else {
					al_draw_bitmap(backsmallmouse1, mouseX, mouseY, 0);
				}
				break;
		}
	}
	al_flip_display();
	return 0;
}

bool checkDown(ALLEGRO_KEYBOARD_STATE state)
{
	if (key_down == false) {
		if (al_key_down(&state, ALLEGRO_KEY_DOWN)) {
			key_down = true;
			return false;
		}
	}
	else {
		if (!(al_key_down(&state, ALLEGRO_KEY_DOWN))) {
			key_down = false;
			return true;
		}
	}
	return false;
}

bool checkUp(ALLEGRO_KEYBOARD_STATE state)
{
	if (key_up == false) {
		if (al_key_down(&state, ALLEGRO_KEY_UP)) {
			key_up = true;
			return false;
		}
	}
	else {
		if (!(al_key_down(&state, ALLEGRO_KEY_UP))) {
			key_up = false;
			return true;
		}
	}
	return false;
}

bool checkRight(ALLEGRO_KEYBOARD_STATE state)
{
	if (al_key_down(&state, ALLEGRO_KEY_RIGHT)) {
		mouseDir = 'f';
		return true;
	}
	return false;
}

bool checkLeft(ALLEGRO_KEYBOARD_STATE state)
{
	if (al_key_down(&state, ALLEGRO_KEY_LEFT)) {
		mouseDir = 'b';
		return true;
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

bool checkFood(ALLEGRO_KEYBOARD_STATE state)
{
	if (waitingFoot == true) {
		if (al_key_down(&state, ALLEGRO_KEY_F) && al_key_down(&state, ALLEGRO_KEY_O) && al_key_down(&state, ALLEGRO_KEY_T)) {
			waitingFoot = false;
			return true;
		}
	}
	return false;
}

int play()
{

	fade(menubck, 0, true, 39);
	fade(levelBackground[level], 0, false, 39);

	mouseDir = 'f';

	al_stop_sample_instance(backgroundMusicInstance);

	levelProgress = 0;
	backgroundX = 0;
	mouseFrames = 0;
	mouse1 = false;
	mouseX = 300;
	targetMouseY = 51;
	mouseY = 51;

	inGame = true;

	while (inGame) {
		ALLEGRO_KEYBOARD_STATE state;
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;

		check_for_restart_gamemusic();

		bool frameUp = false;

		al_get_keyboard_state(&state);

		// Intalize timeout
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

		if (level == 0) {
			for (int i = 0; i < (sizeof(levelOneMapHor) / sizeof(levelOneMapHor[0])); ++i) {
				if (mouseDir == 'f' && levelProgress == levelOneMapHor[i] && mouseY == levelOneMapVer[i]) {
					key_right = false;
					break;
				}
				else if (mouseDir == 'b' && (levelProgress - 300) == levelOneMapHor[i] && mouseY == levelOneMapVer[i]) {
					key_left = false;
					break;
				}
				else {
					key_right = true;
					key_left = true;
				}
			}
		}

		if (targetMouseY > mouseY) {
			mouseY = mouseY + 10;
		}

		else if (targetMouseY < mouseY) {
			mouseY = mouseY - 10;
		}

		if (((mouseFrames + 1) % 11) == 0) {
			mouse1 = !mouse1;
			mouseFrames = mouseFrames + 1;
		}

		if (checkEsc(state)) {
			fade(levelBackground[level], 0, true, 39);
			fade(menubck, 0, false, 39);
			al_stop_sample_instance(gameMusicInstance);
			return 0;
		}

		if (checkLeft(state) && key_left) {
			levelProgress = levelProgress - 10;
			if (mouseX >= 280) {
				mouseX = mouseX - 10;
			}
			else {
				backgroundX = backgroundX + 10;
			}
			if (!frameUp) {
				mouseFrames = mouseFrames + 1;
				frameUp = true;
			}
		}
		if (checkUp(state)) {
			targetMouseY = targetMouseY - 160;
		}
		if (checkDown(state)) {
			targetMouseY = targetMouseY + 160;
		}
		if (checkRight(state) && key_right) {
			levelProgress = levelProgress + 10;
			if (mouseX <= 500) {
				mouseX = mouseX + 10;
			}
			else {
				backgroundX = backgroundX - 10;
			}
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

	al_stop_sample_instance(gameMusicInstance);

	return 0;
}

int credits()
{

	fade(menubck, 0, true, 39);
	fade(creditsbck, 0, false, 39);

	bool inCredits = true;

	bool mouse_button_1 = false;

	drawCredits();

	while (inCredits) {
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		ALLEGRO_MOUSE_STATE state;

		check_for_restart_thememusic();

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

	fade(creditsbck, 0, true, 39);
	fade(menubck, 0, false, 39);

	return 0;
}

int options()
{
	bool inOptions = true;

	bool mouse_button_1 = false;

	fade(menubck, 0, true, 39);

	if (!optionsx) {
		fade(optionsybck, 0, false, 39);
	}
	else {
		fade(optionsxbck, 0, false, 39);
	}

	while (inOptions) {
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		ALLEGRO_MOUSE_STATE state;

		check_for_restart_thememusic();

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
					if (!optionsx) {
						fade(optionsybck, 0, true, 39);
					}
					else {
						fade(optionsxbck, 0, true, 39);
					}
					fade(menubck, 0, false, 39);
					return 0;
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
	al_install_mouse();
	al_install_keyboard();
	fade(menubck, 39, false, 117);
	while (!endProcess) {

		bool mouse_button_1 = false;

		bool inMenu = true;

		if (!optionsx) {
			al_play_sample_instance(backgroundMusicInstance);
		}


		while (inMenu) {
			ALLEGRO_EVENT event;
			ALLEGRO_TIMEOUT timeout;
			ALLEGRO_MOUSE_STATE state;
			ALLEGRO_KEYBOARD_STATE keyState;

			check_for_restart_thememusic();

			al_get_keyboard_state(&keyState);

			checkFood(keyState);

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
					if (state.x >= 0 && state.x <= 100 && state.y >= 507 && state.y <= 640 && waitingFoot == false) {
						easterFoot();
					}
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

		checkSelection();
	}
	al_uninstall_mouse();
	return 0;
}

int main(int argc, char* argv[])
{
	checkSound();

	bool startupDone = false;

	checkLevel();

	// Initializations and setup
	al_init();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_reserve_samples(numSamples);
	al_init_image_addon();
	display = al_create_display(1080, 640);
	al_set_window_title(display, "I Topi Mangiano Gatti");
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	//load samples
	backgroundMusic = al_load_sample("backgroundmusic.wav");
	backgroundMusicInstance = al_create_sample_instance(backgroundMusic);
	al_attach_sample_instance_to_mixer(backgroundMusicInstance, al_get_default_mixer());

	gameMusic = al_load_sample("gamemusic.wav");
	gameMusicInstance = al_create_sample_instance(gameMusic);
	al_attach_sample_instance_to_mixer(gameMusicInstance, al_get_default_mixer());

	// Load images
	finish = al_load_bitmap("finish.png");
	itopimangianogatti = al_load_bitmap("itopimangianogatti.png");
	wanderingrangerstudios = al_load_bitmap("wanderingrangerstudios.png");
	levelBackground[0] = al_load_bitmap("level1.png");
	levelBackground[1] = al_load_bitmap("level2.png");;
	foot = al_load_bitmap("foot.png");
	creditsbck = al_load_bitmap("creditsbck.png");
	optionsybck = al_load_bitmap("optionsybck.png");
	optionsxbck = al_load_bitmap("optionsxbck.png");
	mouse = al_load_bitmap("mouse.png");
	smallmouse = al_load_bitmap("smallmouse.png");
	smallmouse1 = al_load_bitmap("smallmouse1.png");
	backsmallmouse = al_load_bitmap("backsmallmouse.png");
	backsmallmouse1 = al_load_bitmap("backsmallmouse1.png");
	upmouse = al_load_bitmap("upmouse.png");
	bckground = al_load_bitmap("bckground.jpeg");
	menubck = al_load_bitmap("menubck.png");
	houndproductions = al_load_bitmap("houndproductions.png");

	// Clear screen to black
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	// Hound Productions
	fade(houndproductions, 78, false, 156);
	if (!endProcess) fade(houndproductions, 234, true, 312);

	// Wandering Ranger Studios
	if (!endProcess) fade(wanderingrangerstudios, 78, false, 156);
	if (!endProcess) fade(wanderingrangerstudios, 234, true, 312);

	// I Topi Mangiano Gatti
	if (!endProcess) fade(itopimangianogatti, 78, false, 156);
	if (!endProcess) fade(itopimangianogatti, 234, true, 312);

	if (endProcess == true) {
		return 0;
	}

	// Loading Screen
	fade(bckground, 78, false, 156);
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
			fade(bckground, 39, true, 117);
		}
	}

	menu();

	closeDisplay();

	return 0;
}
