#include "game.h"

#define COLLISION_LEVEL_LEFT 1
#define COLLISION_LEVEL_TOP 2
#define COLLISION_LEVEL_RIGHT 4
#define COLLISION_LEVEL_BOTTOM 8

int actor_level_collision(actor_state *actor);
