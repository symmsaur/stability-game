#include "engine.h"
#include "game.h"
#include "collision.h"
#include "fireguy.h"

void tick_fireguy(fireguy *guy);

// MAXIMUM NUMBER OF FIREGUYS (if you need more, increase it)
#define FIREGUY_CAP 64

#define FIREGUY_SPEED 2

static fireguy *fireguys = NULL;
static int n_fireguys = 0;

void init_fireguy() {
	if (fireguys == NULL) fireguys = malloc(sizeof(fireguy) * FIREGUY_CAP);
	n_fireguys = 0;
}

void create_fireguy(int x, int y) {
	fireguys[n_fireguys].actor_state.x = x;
	fireguys[n_fireguys].actor_state.y = y;
	fireguys[n_fireguys].sprite = create_sprite(FIRE_RUN_LEFT, FIRE_RUN_LEFT_NUM);
	randomize_sprite(fireguys[n_fireguys].sprite);
	fireguys[n_fireguys].move_state = left;
	n_fireguys++;
}

fireguy* get_fireguy(int i) {
	if (i >= n_fireguys) return NULL;
	else return &fireguys[i];
}


void tick_fireguys() {
	for (int i = 0; i < n_fireguys; i++) {
		tick_fireguy(&fireguys[i]);
	}
}

void kill_guy(fireguy *guy) {
	guy->move_state = dead;
	recreate_sprite(guy->sprite, -1, 1);
}

void update_picked_up_guy(fireguy *guy, int x, int y, int flip) {
	int offset;
	if (flip == SPRITE_FLIP_X) {
		set_sprite_flip(guy->sprite, SPRITE_FLIP_X);
		offset = -TILE_PITCH / 2;
	}
	else {
		set_sprite_flip(guy->sprite, 0);
		offset = TILE_PITCH / 2;
	}
	guy->actor_state.x = x + offset;
	guy->actor_state.y = y - TILE_PITCH / 2;
	set_sprite(guy->sprite, guy->actor_state.x, guy->actor_state.y);

}

void fly(fireguy *guy) {
	int flags = update_actor_position(&guy->actor_state);
	if (flags & COLLISION_TOP_FLAG) guy->actor_state.vel_y = -(guy->actor_state.vel_y / 3);
	if (flags & (COLLISION_RIGHT_FLAG | COLLISION_LEFT_FLAG)) guy->actor_state.vel_x = -(guy->actor_state.vel_x / 3);
	if (flags & COLLISION_BOTTOM_FLAG) {
		guy->actor_state.vel_y = -(guy->actor_state.vel_y / 3);
		guy->actor_state.vel_x = (guy->actor_state.vel_x) / 2;
	}
	if (flags != 0 && abs(guy->actor_state.vel_x) < 8 && abs(guy->actor_state.vel_y) < 8) kill_guy(guy);
	guy->actor_state.vel_y += GRAVITATIONAL_ACCELERATION;
}

void tick_fireguy(fireguy *guy) {
	if (guy->move_state == dead || guy->move_state == picked_up) return;
	int tile_pitch = TILE_SIZE * PIXEL_FACTOR;

	// Behavior
	if (guy->move_state == left) {
		guy->actor_state.x -= FIREGUY_SPEED;
		// check bottom left corner for the ground
		if (!check_solid(guy->actor_state.x, guy->actor_state.y + tile_pitch + 1)
			|| check_solid(guy->actor_state.x - 1, guy->actor_state.y)) {
			guy->move_state = right;
		}
	}
	else if (guy->move_state == right) {
		guy->actor_state.x += FIREGUY_SPEED;
		// check bottom right corner for the ground
		if (!check_solid(guy->actor_state.x + tile_pitch, guy->actor_state.y + tile_pitch + 1)
			|| check_solid(guy->actor_state.x + tile_pitch + 1, guy->actor_state.y)) {
			guy->move_state = left;
		}
	}
	else if (guy->move_state == flying) {
		fly(guy);
	}

	// Update sprite
	set_sprite(guy->sprite, guy->actor_state.x, guy->actor_state.y);
	if (global_frame_number % 5 == 0) {
		advance_sprite_frame(guy->sprite);
	}

	if (guy->move_state == left) set_sprite_flip(guy->sprite, SPRITE_FLIP_X);
	else  set_sprite_flip(guy->sprite, 0);
}