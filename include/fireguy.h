#pragma once
#include "game.h"

// TODO: Consider moving this into the c-file to hide the implementation.
// Same for solid grunt.
typedef struct fireguy {
	actor_state actor_state;
	int sprite;
	int vel_x;
	int vel_y;
	move_state move_state;
} fireguy;

void create_fireguy(int x, int y);
void init_fireguy();
fireguy* get_fireguy(int i);
void tick_fireguys();
void kill_guy(fireguy *guy);
void update_picked_up_guy(fireguy *guy, int x, int y, int flip);