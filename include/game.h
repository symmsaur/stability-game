#pragma once

// game logic headers

void init_game();
void player_move(int dir);
void player_jump();
void player_end_jump();
void tick();

typedef struct actor_state {
  int x;
  int y;
} actor_state;
