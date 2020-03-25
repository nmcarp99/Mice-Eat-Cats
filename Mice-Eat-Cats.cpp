#include <fstream>
#include <iostream>
#include <allegro5/allegro.h>
#include <string>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

using namespace std;
const float FPS = 60;
char* userVal;
size_t len;
errno_t appdataErr;
string user;
ALLEGRO_BITMAP* icon = NULL;
ALLEGRO_BITMAP* houndproductions = NULL;
ALLEGRO_BITMAP* itopimangianogatti = NULL;
ALLEGRO_BITMAP* levelBackground[2];
ALLEGRO_BITMAP* wanderingrangerstudios = NULL;
ALLEGRO_BITMAP* levelpassed = NULL;
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
ALLEGRO_BITMAP* houseentryway = NULL;
ALLEGRO_BITMAP* houseentryway1 = NULL;
ALLEGRO_BITMAP* houseentryway2 = NULL;
ALLEGRO_BITMAP* houseentryway3 = NULL;
ALLEGRO_BITMAP* houseentryway4 = NULL;
ALLEGRO_BITMAP* creditsbck1 = NULL;
ALLEGRO_BITMAP* finish = NULL;
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE_INSTANCE* gongInstance = NULL;
ALLEGRO_SAMPLE* gong = NULL;
ALLEGRO_SAMPLE_INSTANCE* horrorSceneInstance = NULL;
ALLEGRO_SAMPLE* horrorScene = NULL;
ALLEGRO_SAMPLE_INSTANCE* backgroundMusicInstance = NULL;
ALLEGRO_SAMPLE* backgroundMusic = NULL;
ALLEGRO_SAMPLE_INSTANCE* gameMusicInstance = NULL;
ALLEGRO_SAMPLE* gameMusic = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;

// Level One Map
int levelOneMapHor[] = {
	100, 400, -610, -290
};

int levelOneMapVer[] = {
	51, 211, 51, 51
};

int levelOneMapHorHor[] = {
	-600, -600
};

int levelOneMapVerHor[] = {
	41, 112
};

int levelOneMapHorHorWidth[] = {
	310, 310
};

// Level Two Map

int levelTwoMapHor[] = {
	480, 480, 480, 480,
	-600, -600, -600, -600
};

int levelTwoMapVer[] = {
	51, 211, 371, 531,
	51, 211, 371, 531
};

// Level Three Map
int levelThreeMapHor[] = {
	-300, -300, -300, -300
};

int levelThreeMapVer[] = {
	51, 211, 371, 531
};

int levelThreeMapHorHor[] = {
	0
};

int levelThreeMapVerHor[] = {
	0
};

int levelThreeMapHorHorWidth[] = {
	0
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
bool key_up_allowed = true;
bool key_down_allowed = true;
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

int fade(ALLEGRO_BITMAP* image, int framesUpTo312, bool trueForOutFalseForIn, int totalLength, bool levelFade = false)
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
				if (levelFade) {
					al_draw_bitmap(levelBackground[level], backgroundX, 0, 0);
					if (backgroundX <= -1 && level != 1) {
						al_draw_bitmap(levelBackground[level], backgroundX + 1080, 0, 0);
					}
					if (level == 1) {
						if (backgroundX < 0) {
							// Draw right black and right wall
							al_draw_filled_rectangle(backgroundX + 1080, 0, 1080, 640, al_map_rgb(0, 0, 0));
							al_draw_filled_rectangle(backgroundX + 1080, 0, backgroundX + 1130, 640, al_map_rgb(156, 42, 42));
						}
						else if (backgroundX > 0) {
							// Draw left black and left wall
							al_draw_filled_rectangle(0, 0, backgroundX, 640, al_map_rgb(0, 0, 0));
							al_draw_filled_rectangle(backgroundX - 50, 0, backgroundX, 640, al_map_rgb(156, 42, 42));
						}
					}
					if (numbackgroundPassed >= 3) {
						al_draw_bitmap(finish, backgroundX + 1080, 0, 0);
					}

					if (level == 0) {
						for (int x = 0; x < sizeof(levelOneMapHor) / sizeof(levelOneMapHor[0]); ++x) {
							al_draw_filled_rectangle((levelOneMapHor[x] - levelProgress) + mouseX + 300, levelOneMapVer[x], (levelOneMapHor[x] - levelProgress) + (mouseX + 310), levelOneMapVer[x] + 61, al_map_rgb(156, 42, 42));
						}
						for (int x = 0; x < sizeof(levelOneMapHorHor) / sizeof(levelOneMapHorHor[0]); ++x) {
							al_draw_filled_rectangle((levelOneMapHorHor[x] - levelProgress) + mouseX + 300, levelOneMapVerHor[x], (levelOneMapHorHor[x] - levelProgress) + (mouseX + 300 + levelOneMapHorHorWidth[x]), levelOneMapVerHor[x] + 10, al_map_rgb(156, 42, 42));
						}
					}
					if (level == 2) {
						for (int x = 0; x < sizeof(levelThreeMapHor) / sizeof(levelThreeMapHor[0]); ++x) {
							al_draw_filled_rectangle((levelThreeMapHor[x] - levelProgress) + mouseX + 300, levelThreeMapVer[x], (levelThreeMapHor[x] - levelProgress) + (mouseX + 310), levelThreeMapVer[x] + 61, al_map_rgb(156, 42, 42));
						}
						for (int x = 0; x < sizeof(levelThreeMapHorHor) / sizeof(levelThreeMapHorHor[0]); ++x) {
							al_draw_filled_rectangle((levelThreeMapHorHor[x] - levelProgress) + mouseX + 300, levelThreeMapVerHor[x], (levelThreeMapHorHor[x] - levelProgress) + (mouseX + 300 + levelThreeMapHorHorWidth[x]), levelThreeMapVerHor[x] + 10, al_map_rgb(156, 42, 42));
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
					al_draw_filled_rectangle(0, 0, 1080, 640, al_map_rgba_f(0, 0, 0, fadeTransparency));
					al_flip_display();
				}
				else {
					redrawFade(image, fadeTransparency);
				}
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
	fstream openfile(user+"\\level.txt", fstream::in);
	int text;
	openfile>>text;
	openfile.close();
	level = text;
	return 0;
}

int changeLevel()
{
	fstream file(user+"\\level.txt", fstream::out);
	file<<level;
	file.close();

	return 0;
}

bool checkSound()
{
	fstream openfile(user+"\\sound.txt", fstream::in);
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

bool checkUser()
{
	for (int x = 0; userVal[x] != NULL; ++x) {
		user += userVal[x];
	}
	return 0;
}

int changeSound()
{
	fstream openfile(user+"\\sound.txt", fstream::in);
	char text;
	openfile >> text;
	openfile.close();
	fstream file(user+"\\sound.txt", fstream::out);
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
	al_destroy_bitmap(icon);
	al_destroy_bitmap(creditsbck1);
	al_destroy_bitmap(levelpassed);
	al_destroy_bitmap(houseentryway);
	al_destroy_bitmap(houseentryway1);
	al_destroy_bitmap(houseentryway2);
	al_destroy_bitmap(houseentryway3);
	al_destroy_bitmap(houseentryway4);
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
	al_destroy_sample(gong);
	al_destroy_sample_instance(gongInstance);
	al_destroy_sample(horrorScene);
	al_destroy_sample_instance(horrorSceneInstance);
	al_destroy_sample(backgroundMusic);
	al_destroy_sample_instance(backgroundMusicInstance);

	return 0;
}

int drawCredits(bool secondPage)
{
	if (!secondPage) {
		al_draw_bitmap(creditsbck, 0, 0, 0);
	}
	else {
		al_draw_bitmap(creditsbck1, 0, 0, 0);
	}
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

int options()
{
	bool inOptions = true;

	bool mouse_button_1 = false;

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

int drawLevelEnd(ALLEGRO_BITMAP* bck)
{
	al_draw_bitmap(bck, 0, 0, 0);
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

int levelEnd(ALLEGRO_BITMAP* bck)
{

	fade(levelBackground[level], 39, true, 117, true);
	fade(bck, 39, false, 117);

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
				if (state.x >= 440 && state.x <= 640) {
					if (state.y >= 125 && state.y <= 225) {
						inLevelEnd = false;
						++level;
						fade(bck, 39, true, 117);
						fade(levelBackground[level], 39, false, 117);
						changeLevel();
						numbackgroundPassed = 0;

						return 0;
					}
					else if (state.y >= 225 && state.y <= 325) {
						inLevelEnd = false;
						fade(bck, 39, true, 117);
						fade(levelBackground[level], 39, false, 117);
						numbackgroundPassed = 0;

						return 0;
					}
					else if (state.y >= 325 && state.y <= 425) {
						fade(bck, 0, true, 39);
						options();
						fade(bck, 0, false, 39);
					}
					else if (state.y >= 425 && state.y <= 525) {
						inGame = false;
						inLevelEnd = false;
						++level;
						changeLevel();
						fade(bck, 39, true, 117);
						fade(menubck, 39, false, 117);
						numbackgroundPassed = 0;
						return 0;
					}
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
				drawLevelEnd(bck);
				break;

			}
		}
	}

	return 0;
}

int redrawGame() {
	al_draw_bitmap(levelBackground[level], backgroundX, 0, 0);
	if (backgroundX <= -1 && level != 1) {
		al_draw_bitmap(levelBackground[level], backgroundX + 1080, 0, 0);
	}
	if (level == 1) {
		if (backgroundX < 0) {
			// Draw right black and right wall
			al_draw_filled_rectangle(backgroundX + 1080, 0, 1080, 640, al_map_rgb(0, 0, 0));
			al_draw_filled_rectangle(backgroundX + 1080, 0, backgroundX + 1130, 640, al_map_rgb(156, 42, 42));
		}
		else if (backgroundX > 0) {
			// Draw left black and left wall
			al_draw_filled_rectangle(0, 0, backgroundX, 640, al_map_rgb(0, 0, 0));
			al_draw_filled_rectangle(backgroundX - 50, 0, backgroundX, 640, al_map_rgb(156, 42, 42));
		}
	}
	if (numbackgroundPassed >= 3) {
		al_draw_bitmap(finish, backgroundX + 1080, 0, 0);
		if (backgroundX <= -720) {
			levelEnd(levelpassed);
		}
	}

	if (level == 0) {
		for (int x = 0; x < sizeof(levelOneMapHor) / sizeof(levelOneMapHor[0]); ++x) {
			al_draw_filled_rectangle((levelOneMapHor[x] - levelProgress) + mouseX + 300, levelOneMapVer[x], (levelOneMapHor[x] - levelProgress) + (mouseX + 310), levelOneMapVer[x] + 61, al_map_rgb(156, 42, 42));
		}
		for (int x = 0; x < sizeof(levelOneMapHorHor) / sizeof(levelOneMapHorHor[0]); ++x) {
			al_draw_filled_rectangle((levelOneMapHorHor[x] - levelProgress) + mouseX + 300, levelOneMapVerHor[x], (levelOneMapHorHor[x] - levelProgress) + (mouseX + 300 + levelOneMapHorHorWidth[x]), levelOneMapVerHor[x] + 10, al_map_rgb(156, 42, 42));
		}
	}
	if (level == 2) {
		for (int x = 0; x < sizeof(levelThreeMapHor) / sizeof(levelThreeMapHor[0]); ++x) {
			al_draw_filled_rectangle((levelThreeMapHor[x] - levelProgress) + mouseX + 300, levelThreeMapVer[x], (levelThreeMapHor[x] - levelProgress) + (mouseX + 310), levelThreeMapVer[x] + 61, al_map_rgb(156, 42, 42));
		}
		for (int x = 0; x < sizeof(levelThreeMapHorHor) / sizeof(levelThreeMapHorHor[0]); ++x) {
			al_draw_filled_rectangle((levelThreeMapHorHor[x] - levelProgress) + mouseX + 300, levelThreeMapVerHor[x], (levelThreeMapHorHor[x] - levelProgress) + (mouseX + 300 + levelThreeMapHorHorWidth[x]), levelThreeMapVerHor[x] + 10, al_map_rgb(156, 42, 42));
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

int graphics()
{
	if (level != 1) {
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
	}
	
	redrawGame();

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
	al_stop_sample_instance(backgroundMusicInstance);
	if (level == 0) {

		if (!endProcess) fade(houseentryway, 117, false, 117);
		if (!optionsx && !endProcess) al_play_sample_instance(horrorSceneInstance);
		if (!endProcess) fade(houseentryway, 0, true, 39);
		if (!endProcess) fade(houseentryway, 78, false, 78);
		if (!optionsx && !endProcess) al_stop_sample_instance(horrorSceneInstance);

		if (!optionsx && !endProcess) al_play_sample_instance(horrorSceneInstance);
		if (!endProcess) fade(houseentryway1, 0, true, 39);
		if (!endProcess) fade(houseentryway1, 78, false, 78);
		if (!optionsx && !endProcess) al_stop_sample_instance(horrorSceneInstance);

		if (!optionsx && !endProcess) al_play_sample_instance(horrorSceneInstance);
		if (!endProcess) fade(houseentryway2, 0, true, 39);
		if (!endProcess) fade(houseentryway2, 78, false, 78);
		if (!optionsx && !endProcess) al_stop_sample_instance(horrorSceneInstance);

		if (!optionsx && !endProcess) al_play_sample_instance(horrorSceneInstance);
		if (!endProcess) fade(houseentryway3, 0, true, 39);
		if (!endProcess) fade(houseentryway3, 78, false, 78);
		if (!optionsx && !endProcess) al_stop_sample_instance(horrorSceneInstance);

		if (!optionsx && !endProcess) al_play_sample_instance(horrorSceneInstance);
		if (!endProcess) fade(houseentryway4, 0, true, 39);
		if (!endProcess) fade(houseentryway4, 273, false, 273);
		if (!optionsx && !endProcess) al_stop_sample_instance(horrorSceneInstance);

		if (!optionsx && !endProcess) al_play_sample_instance(gongInstance);
		if (!optionsx && !endProcess) while (al_get_sample_instance_playing(gongInstance)) {}

		if (endProcess) {
			return 0;
		}
	}
	fade(levelBackground[level], 0, false, 39);

	mouseDir = 'f';

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
				if (mouseDir == 'f' && levelProgress == levelOneMapHor[i] && targetMouseY == levelOneMapVer[i]) {
					key_right = false;
					break;
				}
				else if (mouseDir == 'b' && (levelProgress - 310) == levelOneMapHor[i] && targetMouseY == levelOneMapVer[i]) {
					key_left = false;
					break;
				}
				else {
					key_right = true;
					key_left = true;
				}
			}
			for (int i = 0; i < (sizeof(levelOneMapHorHor) / sizeof(levelOneMapHorHor[0])); ++i) {
				if (levelProgress > levelOneMapHorHor[i] && levelProgress < levelOneMapHorHor[i] + 600) {
					if (levelOneMapVerHor[i] == mouseY - 10) {
						key_up_allowed = false;
					}
					else if (levelOneMapVerHor[i] == mouseY + 61) {
						key_down_allowed = false;
					}
				}
				else {
					key_up_allowed = true;
					key_down_allowed = true;
				}
			}
		}

		else if (level == 1) {
			for (int i = 0; i < (sizeof(levelTwoMapHor) / sizeof(levelTwoMapHor[0])); ++i) {
				if (mouseDir == 'f' && levelProgress == levelTwoMapHor[i] && targetMouseY == levelTwoMapVer[i]) {
					key_right = false;
					break;
				}
				else if (mouseDir == 'b' && (levelProgress - 310) == levelTwoMapHor[i] && targetMouseY == levelTwoMapVer[i]) {
					key_left = false;
					break;
				}
				else {
					key_right = true;
					key_left = true;
				}
			}
		}

		else if (level == 2) {
			for (int i = 0; i < (sizeof(levelThreeMapHor) / sizeof(levelThreeMapHor[0])); ++i) {
				if (mouseDir == 'f' && levelProgress == levelThreeMapHor[i] && targetMouseY == levelThreeMapVer[i]) {
					key_right = false;
					break;
				}
				else if (mouseDir == 'b' && (levelProgress - 310) == levelThreeMapHor[i] && targetMouseY == levelThreeMapVer[i]) {
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
			fade(levelBackground[level], 0, true, 39, true);
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
		if (checkUp(state) && key_up_allowed) {
			targetMouseY = targetMouseY - 160;
		}
		if (checkDown(state) && key_down_allowed) {
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
				graphics();
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

	bool secondPage = false;

	bool mouse_button_1 = false;

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
				if (state.x >= 503 && state.x <= 578 && state.y >= 535 && state.y <= 605) {
					if (secondPage) {
						fade(creditsbck1, 0, true, 39);
						fade(creditsbck, 0, false, 39);
					}
					else {
						fade(creditsbck, 0, true, 39);
						fade(creditsbck1, 0, false, 39);
					}
					secondPage = !secondPage;
				}
				else {
					inCredits = false;
				}
				mouse_button_1 = false;
			}
		}

		if (get_event) {
			switch (event.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				inCredits = false;
				endProcess = true;
				break;
			case ALLEGRO_EVENT_TIMER:
				drawCredits(secondPage);
			}
		}
	}

	if (secondPage) {
		fade(creditsbck1, 0, true, 39);
	}
	else {
		fade(creditsbck, 0, true, 39);
	}
	fade(menubck, 0, false, 39);

	return 0;
}

int checkSelection()
{
	switch (selection) {
	case 'p':
		play();
		break;
	case 'o':
		fade(menubck, 0, true, 39);
		options();
		fade(menubck, 0, false, 39);
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

	appdataErr = _dupenv_s(&userVal, &len, "APPDATA");
	if (appdataErr) return -1;
	checkUser();
	free(userVal);

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

	horrorScene = al_load_sample("horrorscene.wav");
	horrorSceneInstance = al_create_sample_instance(horrorScene);
	al_attach_sample_instance_to_mixer(horrorSceneInstance, al_get_default_mixer());

	gong = al_load_sample("gong.wav");
	gongInstance = al_create_sample_instance(gong);
	al_attach_sample_instance_to_mixer(gongInstance, al_get_default_mixer());

	gameMusic = al_load_sample("gamemusic.wav");
	gameMusicInstance = al_create_sample_instance(gameMusic);
	al_attach_sample_instance_to_mixer(gameMusicInstance, al_get_default_mixer());

	// Load images
	finish = al_load_bitmap("finish.png");
	icon = al_load_bitmap("icon.png");
	levelpassed = al_load_bitmap("levelpassed.png");
	houseentryway = al_load_bitmap("houseentryway.png");
	houseentryway1 = al_load_bitmap("houseentryway1.png");
	houseentryway2 = al_load_bitmap("houseentryway2.png");
	houseentryway3 = al_load_bitmap("houseentryway3.png");
	houseentryway4 = al_load_bitmap("houseentryway4.png");
	itopimangianogatti = al_load_bitmap("itopimangianogatti.png");
	wanderingrangerstudios = al_load_bitmap("wanderingrangerstudios.png");
	levelBackground[0] = al_load_bitmap("level1.png");
	levelBackground[1] = al_load_bitmap("level2.png");;
	foot = al_load_bitmap("foot.png");
	creditsbck = al_load_bitmap("creditsbck.png");
	creditsbck1 = al_load_bitmap("creditsbck1.png");
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

	al_set_display_icon(display, icon);

	// Clear screen to black
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	// Hound Productions
	if (!endProcess) fade(houndproductions, 78, false, 156);
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
