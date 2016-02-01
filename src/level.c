#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "tiles.h"
#include "game.h"
#include "engine.h"
#include "level.h"
#include "fireguy.h"
#include "solidgrunt.h"

void load_level(const char* filename, int in_editor){
	int tile_pitch = TILE_SIZE * PIXEL_FACTOR;
	FILE* lvl_file;
	lvl_file = fopen(filename, "r");
  // TODO: check for null
  for(int y = 0; y < BG_TILES_Y; y++){
    for (int x = 0; x < BG_TILES_X; x++){
		int c = fgetc(lvl_file);
		if (!in_editor) {
			if (c == FIRE_RUN_LEFT) {
				create_fireguy(x * tile_pitch, y * tile_pitch);
				c = SKY;
			}
			if (c == SOLIDGRUNT_RUN_LEFT) {
				create_solidgrunt(x * tile_pitch, y * tile_pitch);
				c = SKY;
			}
			if (c == CHR_RUN_LEFT) {
				set_player_pos(x * tile_pitch, y * tile_pitch);
				c = SKY;
			}
		}
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
  fclose(lvl_file);
}

static char* _level_path = NULL;
// dammit
char* get_level_path(int level_num) {
	if (_level_path == NULL) {
		_level_path = malloc(sizeof(char) * 256);
		const char* orig_path = "../assets/level1.lvl";
		strncpy(_level_path, orig_path, 256);
	}
	_level_path[15] = "0123456789"[level_num];
	return _level_path;
}


