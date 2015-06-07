#include <stdio.h>

#include "engine.h"
#include "level.h"

int get_next_tile(FILE* lvl_file);

void load_level(const char* filename){
  FILE* lvl_file = fopen(filename, "r");
  for(int y = 0; y < BG_TILES_Y; y++){
    for (int x = 0; x < BG_TILES_X; x++){
        set_bg_tile(x, y, fgetc(lvl_file));
    }
  }
}

