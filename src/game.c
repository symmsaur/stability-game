#include "game.h"
#include "engine.h"
#include "level.h"

#define ON_GROUND 1

void player_tick();

struct player_state {
  int sprite;
  int x;
  int y;
  int vel_x;
  int vel_y;
  int jmp_frames;
  int state;
};

static struct player_state player;

void init_game(){
  load_level("../assets/level1.lvl");
  player.sprite = create_sprite(CHR_RUN_LEFT, CHR_RUN_LEFT_NUM);
  player.x = SCREEN_WIDTH / 2;
  player.y = SCREEN_HEIGHT / 2;
  player.vel_x = 0;
  player.vel_y = 0;
  player.jmp_frames = 0;
  player.state = 0;
}

void player_move(int dir){
  const int max_speed = 32;
  if (dir > 0) {
    if (player.vel_x < 0) player.vel_x += 6;
    else if (player.vel_x < max_speed) player.vel_x += 4;
    if (player.vel_x >= max_speed) player.vel_x = max_speed;
  }
  if (dir < 0) {
    if (player.vel_x > 0) player.vel_x -= 6;
    else if (player.vel_x > -max_speed) player.vel_x -= 4;
    if (player.vel_x <= max_speed) player.vel_x = -max_speed;
  }

}

void player_jump() {
  if (player.state & ON_GROUND){
    player.jmp_frames = 10;
  }
  if (player.jmp_frames > 0)
  {
    player.vel_y -= 12;
  }
}

// TODO: Improve
int player_level_collision() {
  int tile_x = player.x / (TILE_SIZE * PIXEL_FACTOR);
  int tile_y = player.y / (TILE_SIZE * PIXEL_FACTOR);

  //printf("(%d, %d)", tile_x, tile_y);
  //printf(":%d ", get_bg_tile(tile_x, tile_y));
  if (get_bg_tile(tile_x, tile_y) == DARK_STONE) return 1;
  if (get_bg_tile(tile_x, tile_y + 1 ) == DARK_STONE) return 2;
  if (get_bg_tile(tile_x + 1, tile_y) == DARK_STONE) return 1;
  if (get_bg_tile(tile_x + 1, tile_y + 1) == DARK_STONE) return 2;

  return 0;
}

void tick(){
  player_tick();
}

void player_tick(){
  int collision;
  //struct player_state old_player = player;
  //struct player_state new_player = player;
  
  player.state = 0;

  if (player.jmp_frames > 0) player.jmp_frames--;

  player.x += (player.vel_x >> 3);
  player.y += (player.vel_y >> 3);

  collision = player_level_collision();
  if(collision == 1){
    player.vel_x = 0;
  }
  else if (collision == 2){
    player.y -= player.vel_y >> 3;
    player.vel_y = 0;
    player.state |= ON_GROUND;
  }

  if (player.vel_x > 0) player.vel_x -= 2;
  else if (player.vel_x < 0) player.vel_x += 2;
  if (player.vel_x == -1 || player.vel_x == 1) player.vel_x = 0;

  if (player.vel_y < 64 && !(player.state & ON_GROUND) && player.jmp_frames == 0) player.vel_y += 8;

  set_sprite(player.sprite, player.x, player.y);
  if (!(frame_number % 5)) advance_sprite_frame(player.sprite);
}
