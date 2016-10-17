#include "main.h"

const Uint8 *key_state;

static SDL_GameController *controller;

void print_stats();
int init_controllers();

int main(int argc, const char *argv[]) {
	int res;
	printf("Starting...\n");
	init_engine();

	res = init_controllers();

	res = load_assets();
	if (res != 0) {
		printf("Failed loading assets");
		SDL_Quit();
	}

	init_game(1);

	key_state = SDL_GetKeyboardState(NULL);

	printf("Ready\n");
	while (1) {
		int ce = SDL_GameControllerGetAttached(controller);
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) break;
		}
		if (key_state[SDL_SCANCODE_ESCAPE]) break;
		if (key_state[SDL_SCANCODE_LEFT] ||
			(ce && SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))) {
			player_move(-1);
		}
		if (key_state[SDL_SCANCODE_RIGHT] ||
			(ce && SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))) {
			player_move(1);
		}
		if (key_state[SDL_SCANCODE_SPACE] ||
			(ce && SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A))) {
			player_jump();
		}
		else {
			player_end_jump();
		}
		if (key_state[SDL_SCANCODE_LCTRL] ||
			(ce && SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X))) {
			player_enable_pickup(1);
		}
		else {
			player_enable_pickup(0);
		}

		if (key_state[SDL_SCANCODE_E] && key_state[SDL_SCANCODE_LSHIFT]) {
			clear_sprites();
			init_editor(get_current_level());
			editor_loop();
			init_game(get_current_level());
		}

		// Level warps
		// Start screen
		if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_0]) {
			init_game(0);
		}
		if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_1]) {
			init_game(1);
		}
		if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_2]) {
			init_game(2);
		}
		if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_3]) {
			init_game(3);
		}
		if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_4]) {
			init_game(4);
		}
		if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_5]) {
			init_game(5);
		}
		// Win screen
		if (key_state[SDL_SCANCODE_LCTRL] && key_state[SDL_SCANCODE_6]) {
			init_game(6);
		}

		tick();
		render_frame();
	}
	printf("Shutting down...\n");
	shutdown_engine();

	print_stats();

	SDL_Quit();
	return 0;
}

// Windows support
int wmain() {
	return main(0, NULL);
}

void print_stats() {
	printf("bg_tiles_x: %d\n", BG_TILES_X);
	printf("bg_tiles_y: %d\n", BG_TILES_Y);
}

int init_controllers() {
	controller = NULL;
	int n_joysticks = SDL_NumJoysticks();
	for (int i = 0; i < n_joysticks; i++) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			return 0;
		}
	}
	return 1;
}

