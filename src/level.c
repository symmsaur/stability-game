#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "main.h"
#include "tiles.h"
#include "game.h"

#include "engine.h"
#include "level.h"

void load_level(const char* filename){
	int tile_pitch = TILE_SIZE * PIXEL_FACTOR;
	FILE* lvl_file;
	lvl_file = fopen(filename, "r");
  // TODO: check for null
  for(int y = 0; y < BG_TILES_Y; y++){
    for (int x = 0; x < BG_TILES_X; x++){
		int c = fgetc(lvl_file);
#ifndef EDITOR
		if (c == FIRE_RUN_LEFT) {
			create_fireguy(x * tile_pitch, y * tile_pitch);
			c = SKY;
		}
#endif
        set_bg_tile(x, y, c);
    }
  }
}

void save_level(const char* filename){
  FILE* lvl_file;
  lvl_file = fopen(filename, "w");
  // TODO: check for null
  for(int y = 0; y < BG_TILES_Y; y++){
    for (int x = 0; x < BG_TILES_X; x++){
      fputc(get_bg_tile(x,y), lvl_file);
    }
  }
}

