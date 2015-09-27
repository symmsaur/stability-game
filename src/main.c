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

	init_game();

	key_state = SDL_GetKeyboardState(NULL);

	printf("Ready\n");
	while (1) {
		bool ce = SDL_GameControllerGetAttached(controller);
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) break;
		}
		if (key_state[SDL_SCANCODE_ESCAPE]) break;
		if (key_state[SDL_SCANCODE_LEFT] ||
			ce && SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)
			) {
			player_move(-1);
		}
		if (key_state[SDL_SCANCODE_RIGHT] ||
			ce && SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
			) {
			player_move(1);
		}
		if (key_state[SDL_SCANCODE_SPACE] ||
			ce && SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)
			) {
			player_jump();
		}
		else {
			player_end_jump();
		}

		if (key_state[SDL_SCANCODE_E] && key_state[SDL_SCANCODE_LSHIFT]) {
			clear_sprites();
			init_editor();
			editor_loop();
			init_game();
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

