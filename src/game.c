#include "game.h"
#include "engine.h"

static int player_sprite;
static int player_x;
static int player_y;

void init_game(){
  for(int x = 0; x < BG_TILES_X; x++){
    for (int y = 0; y < BG_TILES_Y; y++){
      set_bg_tile(x, y, rand() % TILES_X * BG_TILES_Y);
    }
  }

  player_sprite = create_sprite(CHR_RUN_LEFT, CHR_RUN_LEFT_NUM);
  player_x = SCREEN_WIDTH / 2;
  player_y = SCREEN_HEIGHT / 2;
  set_sprite(player_sprite, player_x, player_y);
}

void move_player(int dx){
  player_x += dx;
  set_sprite(player_sprite, player_x, player_y);
  if (!(frame_number % 6)) advance_sprite_frame(player_sprite);
}
