#pragma once

#define GRAVITATIONAL_ACCELERATION 6

#define COLLISION_TOP_FLAG 1
#define COLLISION_RIGHT_FLAG 2
#define COLLISION_BOTTOM_FLAG 4
#define COLLISION_LEFT_FLAG 8

typedef struct fireguy fireguy;
typedef struct actor_state {
  int x;
  int y;
  int vel_x;
  int vel_y;
} actor_state;

void init_game();
void set_player_pos(int x, int y);
void player_move(int dir);
void player_jump();
void player_end_jump();
void player_pickup_guy(fireguy *guy);
actor_state* get_player_actor_state();
void player_enable_pickup(int enable);
int update_actor_position(actor_state *actor);
void tick();

int global_frame_number;

typedef enum {
	left, right, up, down, flying, picked_up, dead, climbing_up, falling
} move_state;
