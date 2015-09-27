#include "game.h"

#define COLLISION_LEVEL_LEFT 1
#define COLLISION_LEVEL_TOP 2
#define COLLISION_LEVEL_RIGHT 4
#define COLLISION_LEVEL_BOTTOM 8

int actor_level_collision(int x, int y);
int actor_actor_collision(actor_state state1, actor_state state2);
int check_solid(int x, int y);