#include "engine.h"
#include "game.h"
#include "collision.h"
#include "fireguy.h"

void tick_fireguy(fireguy *guy);

// MAXIMUM NUMBER OF FIREGUYS (if you need more, increase it)
#define FIREGUY_CAP 64

#define FIREGUY_SPEED 2

static fireguy *fireguys;
static int n_fireguys = 0;

void init_fireguy() {
	fireguys = malloc(sizeof(fireguy) * FIREGUY_CAP);
}

int create_fireguy(int x, int y) {
	fireguys[n_fireguys].actor_state.x = x;
	fireguys[n_fireguys].actor_state.y = y;
	fireguys[n_fireguys].sprite = create_sprite(FIRE_RUN_LEFT, FIRE_RUN_LEFT_NUM );
	fireguys[n_fireguys].move_state = left;
	n_fireguys++;
}

void tick_fireguys() {
	for (int i = 0; i < n_fireguys; i++) {
		tick_fireguy(&fireguys[i]);
	}
}

void tick_fireguy(fireguy *guy) {
	static int frame_n = 0;
	int tile_pitch = TILE_SIZE * PIXEL_FACTOR;

	// Behavior
	if (guy->move_state == left) {
		guy->actor_state.x -= FIREGUY_SPEED;
		// check bottom left corner for the ground
		if (!check_solid(guy->actor_state.x, guy->actor_state.y + tile_pitch + 1))
		{
			guy->move_state = right;
		}
	}
	else {
		guy->actor_state.x += FIREGUY_SPEED;
		// check bottom right corner for the ground
		if (!check_solid(guy->actor_state.x + tile_pitch, guy->actor_state.y + tile_pitch + 1))
		{
			guy->move_state = left;
		}
	}

	// Update sprite
	set_sprite(guy->sprite, guy->actor_state.x, guy->actor_state.y);
	if (frame_n % 5 == 0) {
		advance_sprite_frame(guy->sprite);
	}

	if (guy->move_state == left) set_sprite_flip(guy->sprite, SPRITE_FLIP_X);
	else  set_sprite_flip(guy->sprite, 0);
	frame_n++;
}