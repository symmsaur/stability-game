#include "game.h"
#include "engine.h"
#include "level.h"

// FLAGS
#define ON_GROUND 1

// MOVEMENT CONSTANTS
#define PLAYER_DECELERATION 6
#define PLAYER_ACCELERATION 4
#define PLAYER_MAX_SPEED 32
#define PLAYER_JUMP_SPEED (-64)
#define PLAYER_JUMP_FRAMES 15
#define GRAVITATIONAL_ACCELERATION 8
#define MAX_FALL_SPEED 64


void player_tick();
int check_solid(int x, int y);

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
  if (dir > 0) {
    if (player.vel_x < 0) player.vel_x += PLAYER_DECELERATION ;
    else  player.vel_x += PLAYER_ACCELERATION;

    if (player.vel_x >= PLAYER_MAX_SPEED) player.vel_x = PLAYER_MAX_SPEED;
  }
  if (dir < 0) {
    if (player.vel_x > 0) player.vel_x -= PLAYER_DECELERATION;
    else player.vel_x -= PLAYER_ACCELERATION;

    if (player.vel_x <= -PLAYER_MAX_SPEED) player.vel_x = -PLAYER_MAX_SPEED;
  }

}

void player_jump() {
  if (player.state & ON_GROUND){
    player.jmp_frames = PLAYER_JUMP_FRAMES;
  }
  if (player.jmp_frames > 0)
  {
    player.vel_y = PLAYER_JUMP_SPEED;
  }
}

void player_end_jump() {
  player.jmp_frames = 0;
}

// TODO: Improve
int player_level_collision(){
  int tile_x = player.x / (TILE_SIZE * PIXEL_FACTOR);
  int tile_y = player.y / (TILE_SIZE * PIXEL_FACTOR);

  //printf("(%d, %d)", tile_x, tile_y);
  //printf(":%d ", get_bg_tile(tile_x, tile_y));
  if (check_solid(tile_x, tile_y)) return 1;
  if (check_solid(tile_x, tile_y + 1 )) return 2;
  if (check_solid(tile_x + 1, tile_y)) return 1;
  if (check_solid(tile_x + 1, tile_y + 1)) return 2;

  return 0;
}

int check_solid(int x, int y){
  return get_bg_tile(x, y) <= MAX_SOLID_TILE &&
    get_bg_tile(x, y) >= MIN_SOLID_TILE;
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

  if (player.vel_y < MAX_FALL_SPEED && !(player.state & ON_GROUND) && player.jmp_frames == 0) {
    player.vel_y += GRAVITATIONAL_ACCELERATION;
  }

  set_sprite(player.sprite, player.x, player.y);
  if (!(frame_number % 5)) advance_sprite_frame(player.sprite);
}
