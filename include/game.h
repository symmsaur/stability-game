#pragma once
//#include "fireguy.h"

// game logic headers

typedef struct fireguy fireguy;
typedef struct actor_state {
  int x;
  int y;
} actor_state;

void init_game();
void set_player_pos(int x, int y);
void player_move(int dir);
void player_jump();
void player_end_jump();
void player_pickup_guy(fireguy *guy);
actor_state* get_player_actor_state();
void player_enable_pickup(int enable);
void tick();

int global_frame_number;


typedef enum {
	left, right, up, down, flying, picked_up, dead
} move_state;
