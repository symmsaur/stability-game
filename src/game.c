#include "game.h"
#include "engine.h"
#include "level.h"
#include "collision.h"

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

struct player_state {
  actor_state actor_state;
  int sprite;
  int jmp_frames;
  int state;
};

static struct player_state player;

void init_game(){
  load_level("../assets/level1.lvl");
  player.sprite = create_sprite(CHR_RUN_LEFT, CHR_RUN_LEFT_NUM);
  player.actor_state.x = SCREEN_WIDTH / 2;
  player.actor_state.y = SCREEN_HEIGHT / 2;
  player.actor_state.vel_x = 0;
  player.actor_state.vel_y = 0;
  player.jmp_frames = 0;
  player.state = 0;
}

void player_move(int dir){
  if (dir > 0) {
    if (player.actor_state.vel_x < 0) player.actor_state.vel_x += PLAYER_DECELERATION ;
    else  player.actor_state.vel_x += PLAYER_ACCELERATION;

    if (player.actor_state.vel_x >= PLAYER_MAX_SPEED) player.actor_state.vel_x = PLAYER_MAX_SPEED;
  }
  if (dir < 0) {
    if (player.actor_state.vel_x > 0) player.actor_state.vel_x -= PLAYER_DECELERATION;
    else player.actor_state.vel_x -= PLAYER_ACCELERATION;

    if (player.actor_state.vel_x <= -PLAYER_MAX_SPEED) player.actor_state.vel_x = -PLAYER_MAX_SPEED;
  }
}

void player_jump() {
  if (player.state & ON_GROUND){
    player.jmp_frames = PLAYER_JUMP_FRAMES;
  }
  if (player.jmp_frames > 0)
  {
    player.actor_state.vel_y = PLAYER_JUMP_SPEED;
  }
}

void player_end_jump() {
  player.jmp_frames = 0;
}


void tick(){
  player_tick();
}

void player_tick(){
  static int adv_player_frame = 50;
  int collision;
  //struct player_state old_player = player;
  //struct player_state new_player = player;
  
  player.state = 0;

  if (player.jmp_frames > 0) player.jmp_frames--;

  // Update player position
  player.actor_state.x += (player.actor_state.vel_x >> 3);
  player.actor_state.y += (player.actor_state.vel_y >> 3);

  // Handle player collisions.
  collision = actor_level_collision(&player.actor_state);
  if(collision == 1){
    player.actor_state.vel_x = 0;
  }
  else if (collision == 2){
    player.actor_state.y -= player.actor_state.vel_y >> 3;
    player.actor_state.vel_y = 0;
    player.state |= ON_GROUND;
  }

  // Decelerate player
  if (player.actor_state.vel_x > 0) player.actor_state.vel_x -= 2;
  else if (player.actor_state.vel_x < 0) player.actor_state.vel_x += 2;

  // Make sure the player velocity reaches zero.
  if (player.actor_state.vel_x == -1 || player.actor_state.vel_x == 1) player.actor_state.vel_x = 0;

  // Player should fall if not on ground.
  if (player.actor_state.vel_y < MAX_FALL_SPEED && !(player.state & ON_GROUND) && player.jmp_frames == 0) {
    player.actor_state.vel_y += GRAVITATIONAL_ACCELERATION;
  }

  // Animate player sprite depending on how fast the player is moving.
  set_sprite(player.sprite, player.actor_state.x, player.actor_state.y);
  if (adv_player_frame > 0){
    adv_player_frame -= (10 * abs(player.actor_state.vel_x)) / (PLAYER_MAX_SPEED );
  }
  else{
    advance_sprite_frame(player.sprite);
    adv_player_frame = 50;
  }
    
  if (player.actor_state.vel_x < 0) set_sprite_flip(player.sprite, SPRITE_FLIP_X);
  else if (player.actor_state.vel_x > 0) set_sprite_flip(player.sprite, 0);
}
