#include "collision.h"
#include "engine.h"

int check_solid(int x, int y);

int check_solid(int x, int y) {
	int tile_x = x / (TILE_SIZE * PIXEL_FACTOR);
	int tile_y = y / (TILE_SIZE * PIXEL_FACTOR);
	return get_bg_tile(tile_x, tile_y) <= MAX_SOLID_TILE &&
		get_bg_tile(tile_x, tile_y) >= MIN_SOLID_TILE;
}

// Check collisions between an actor and the level
int actor_level_collision(int x, int y) {

	int tile_pitch = TILE_SIZE * PIXEL_FACTOR;
	int margin = tile_pitch / 8;


	if (check_solid(x + margin, y + margin * 2) || 
		check_solid(x + tile_pitch - 1 - margin, y + margin * 2) ||
		check_solid(x + margin, y + tile_pitch - 1) ||
		check_solid(x + tile_pitch - 1 - margin,  y + tile_pitch - 1)) {
		return 1;
	}
	else return 0;
}

// Check actor-actor collisions
// int? actor_actor_collision(struct actor_state *actor1, struct actor_state *actor2)
// {}
