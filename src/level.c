#include <stdio.h>

#include "engine.h"
#include "level.h"

void load_level(const char* filename){
	FILE* lvl_file;
	fopen_s(&lvl_file, filename, "r");
  for(int y = 0; y < BG_TILES_Y; y++){
    for (int x = 0; x < BG_TILES_X; x++){
        set_bg_tile(x, y, fgetc(lvl_file));
    }
  }
}

void save_level(const char* filename){
  FILE* lvl_file;
  fopen_s(&lvl_file, filename, "w");
  for(int y = 0; y < BG_TILES_Y; y++){
    for (int x = 0; x < BG_TILES_X; x++){
      fputc(get_bg_tile(x,y), lvl_file);
    }
  }
}

