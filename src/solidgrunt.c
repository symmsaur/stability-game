#include "engine.h"
#include "game.h"
#include "collision.h"
#include "solidgrunt.h"

void tick_solidgrunt(solidgrunt *grunt);

// Increase if needed
#define SOLIDGRUNT_CAP 64
#define SOLIDGRUNT_SPEED 1

static solidgrunt *solidgrunts = NULL;
static int n_solidgrunts = 0;

void init_solidgrunt() {
	if (solidgrunts == NULL) solidgrunts = malloc(sizeof(solidgrunt) * SOLIDGRUNT_CAP);
	n_solidgrunts = 0;
}

void create_solidgrunt(int x, int y) {
	solidgrunts[n_solidgrunts].actor_state.x = x;
	solidgrunts[n_solidgrunts].actor_state.y = y;
	solidgrunts[n_solidgrunts].sprite = create_sprite(SOLIDGRUNT_RUN_LEFT, SOLIDGRUNT_RUN_LEFT_NUM);
	randomize_sprite(solidgrunts[n_solidgrunts].sprite);
	solidgrunts[n_solidgrunts].move_state = right;
	n_solidgrunts++;
}

void tick_solidgrunts() {
	for (int i = 0; i < n_solidgrunts; i++) {
		tick_solidgrunt(&solidgrunts[i]);
	}
}

void tick_solidgrunt(solidgrunt *grunt) {
	int tile_pitch = TILE_SIZE * PIXEL_FACTOR;

	// Behavior
	if (grunt->move_state == left) {
		grunt->actor_state.x -= SOLIDGRUNT_SPEED;
		if (!check_solid(grunt->actor_state.x, grunt->actor_state.y + tile_pitch + 1)
			|| check_solid(grunt->actor_state.x-1, grunt->actor_state.y)) {
			grunt->move_state = right;
		}
	}
	else if (grunt->move_state == right) {
		grunt->actor_state.x += SOLIDGRUNT_SPEED;
		if (!check_solid(grunt->actor_state.x + tile_pitch, grunt->actor_state.y + tile_pitch + 1)
			|| check_solid(grunt->actor_state.x + tile_pitch + 1, grunt->actor_state.y)) {
			grunt->move_state = left;
		}
	}

	// Update sprite
	set_sprite(grunt->sprite, grunt->actor_state.x, grunt->actor_state.y);
	if (global_frame_number % 8 == 0) {
		advance_sprite_frame(grunt->sprite);
	}

	if (grunt->move_state == left) set_sprite_flip(grunt->sprite, SPRITE_FLIP_X);
	else set_sprite_flip(grunt->sprite, 0);
}