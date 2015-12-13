#include "collision.h"
#include "engine.h"

#define MARGIN (TILE_PITCH / 8) 

int check_solid(int x, int y);

int check_solid(int x, int y) {
	int tile_x = x / TILE_PITCH;
	int tile_y = y / TILE_PITCH;
	return get_bg_tile(tile_x, tile_y) <= MAX_SOLID_TILE &&
		get_bg_tile(tile_x, tile_y) >= MIN_SOLID_TILE;
}

int at_ladder(int x, int y) {
	// Do we line up perfectly?
	int mod_pos = x % TILE_PITCH;
	if (mod_pos != 0) return 0;

	y += TILE_PITCH - 1;
	int tile_x = x / TILE_PITCH;
	int tile_y = y / TILE_PITCH;
	return get_bg_tile(tile_x, tile_y) <= MAX_LADDER_TILE &&
		get_bg_tile(tile_x, tile_y) >= MIN_LADDER_TILE;

}

int actor_level_collision(int x, int y) {
	int margin = TILE_PITCH / 8;

	if (check_solid(x + margin, y + margin * 2) || 
		check_solid(x + TILE_PITCH - 1 - margin, y + margin * 2) ||
		check_solid(x + margin, y + TILE_PITCH - 1) ||
		check_solid(x + TILE_PITCH - 1 - margin,  y + TILE_PITCH - 1)) {
		return 1;
	}
	else return 0;
}

int actor_actor_collision(actor_state state1, actor_state state2) {
	int delta_x = abs(state1.x - state2.x);
	int delta_y = abs(state1.y - state2.y);

	if (delta_x < TILE_PITCH - 2 * MARGIN
		&& delta_y < TILE_PITCH - 2 * MARGIN) return 1;
	else return 0;
}
