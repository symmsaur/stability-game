#include <stdio.h>

// Squash error message for fopen on Windows.
#define _CRT_SECURE_NO_DEPRECATE

#include "engine.h"
#include "level.h"

void load_level(const char* filename){
	FILE* lvl_file;
	lvl_file = fopen(filename, "r");
  // TODO: check for null
  for(int y = 0; y < BG_TILES_Y; y++){
    for (int x = 0; x < BG_TILES_X; x++){
        set_bg_tile(x, y, fgetc(lvl_file));
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

