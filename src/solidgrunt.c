#include "engine.h"
#include "game.h"
#include "collision.h"
#include "solidgrunt.h"
#include "fireguy.h"

void tick_solidgrunt(solidgrunt *grunt);

// Increase if needed
#define SOLIDGRUNT_CAP 64
#define SOLIDGRUNT_SPEED 1
#define SOLIDGRUNT_CLIMB_SPEED 1

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

solidgrunt* get_solidgrunt(int i) {
	if (i >= n_solidgrunts) return NULL;
	else return &solidgrunts[i];
}

void tick_solidgrunts() {
	for (int i = 0; i < n_solidgrunts; i++) {
		tick_solidgrunt(&solidgrunts[i]);
	}
}

void kill_grunt(solidgrunt *grunt) {
	grunt->move_state = dead;
	recreate_sprite(grunt->sprite, -1, 1);
}

int more_guys_above(solidgrunt *grunt) {
	int n_above = 0;
	int n_below = 0;
	fireguy *guy;
	for (int i = 0; guy = get_fireguy(i); i++) {
		if (guy->move_state == dead) continue;
		if (guy->actor_state.y < grunt->actor_state.y) n_above++;
		else n_below++;
	}
	return n_above > n_below;
}

void tick_solidgrunt(solidgrunt *grunt) {
	int tile_pitch = TILE_SIZE * PIXEL_FACTOR;

	// Behavior
	if (grunt->move_state == dead) return;
	else if (grunt->actor_state.x % TILE_PITCH == 0
		&& !check_solid(grunt->actor_state.x, grunt->actor_state.y + TILE_PITCH)
		&& !at_ladder(grunt->actor_state.x, grunt->actor_state.y)
		&& grunt->move_state != falling) {
		grunt->move_state = falling;
		grunt->actor_state.vel_x = 0;
		grunt->actor_state.vel_y = 0;
	}
	else if (grunt->move_state == left) {
		grunt->actor_state.x -= SOLIDGRUNT_SPEED;
		if (at_ladder(grunt->actor_state.x, grunt->actor_state.y)
			&& more_guys_above(grunt)) {
			grunt->move_state = climbing_up;
		}
		else if ((!check_solid(grunt->actor_state.x, grunt->actor_state.y + tile_pitch + 1)
			|| check_solid(grunt->actor_state.x - 1, grunt->actor_state.y))
			&& more_guys_above(grunt)) {
			grunt->move_state = right;
		}
		// add something about falling off the edge
	}
	else if (grunt->move_state == right) {
		grunt->actor_state.x += SOLIDGRUNT_SPEED;
		if (at_ladder(grunt->actor_state.x, grunt->actor_state.y)
			&& more_guys_above(grunt)) {
			grunt->move_state = climbing_up;
		}
		if ((!check_solid(grunt->actor_state.x + tile_pitch, grunt->actor_state.y + tile_pitch + 1)
			|| check_solid(grunt->actor_state.x + tile_pitch + 1, grunt->actor_state.y)) 
			&& more_guys_above(grunt)) {
			grunt->move_state = left;
		}
		// add something about falling off the edge
	}
	else if (grunt->move_state == climbing_up) {
		if (!at_ladder(grunt->actor_state.x, grunt->actor_state.y)) {
			grunt->move_state = left;
		}
		else {
			grunt->actor_state.y -= SOLIDGRUNT_CLIMB_SPEED;
		}
	}
	else if (grunt->move_state == falling) {
		grunt->actor_state.vel_y += GRAVITATIONAL_ACCELERATION;
		if (update_actor_position(&grunt->actor_state) == COLLISION_BOTTOM_FLAG) {
			grunt->move_state = right;
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