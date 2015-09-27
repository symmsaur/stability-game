#pragma once

// game logic headers

void init_game();
void set_player_pos(int x, int y);
void player_move(int dir);
void player_jump();
void player_end_jump();
void tick();

int global_frame_number;

typedef struct {
  int x;
  int y;
} actor_state;

typedef enum {
	left, right, up, down, flying, dead
} move_state;
