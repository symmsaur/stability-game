#include "collision.h"
#include "engine.h"

int check_solid(int x, int y);

int check_solid(int x, int y){
  return get_bg_tile(x, y) <= MAX_SOLID_TILE &&
    get_bg_tile(x, y) >= MIN_SOLID_TILE;
}

// Check collisions between an actor and the level
int actor_level_collision(actor_state *actor)
{
  int tile_x = actor->x / (TILE_SIZE * PIXEL_FACTOR);
  int tile_y = actor->y / (TILE_SIZE * PIXEL_FACTOR);

  //printf("(%d, %d)", tile_x, tile_y);
  //printf(":%d ", get_bg_tile(tile_x, tile_y));
  if (check_solid(tile_x, tile_y)) return 1;
  if (check_solid(tile_x, tile_y + 1 )) return 2;
  if (check_solid(tile_x + 1, tile_y)) return 1;
  if (check_solid(tile_x + 1, tile_y + 1)) return 2;

  return 0;
}

// Check actor-actor collisions
// int? actor_actor_collision(struct actor_state *actor1, struct actor_state *actor2)
// {}
