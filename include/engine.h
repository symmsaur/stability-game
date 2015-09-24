#include "SDL.h"
#include "SDL_image.h"

#include "tiles.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PIXEL_FACTOR 2

#define BG_TILES_X SCREEN_WIDTH / (TILE_SIZE * PIXEL_FACTOR)
#define BG_TILES_Y SCREEN_HEIGHT / (TILE_SIZE * PIXEL_FACTOR)

#define SPRITE_FLIP_X 1
#define SPRITE_FLIP_Y 2

// GLOBALS
int frame_number;

void init_engine();
int load_assets();
int shutdown_engine();

int render_frame();

void set_bg_tile(int x, int y, int tile_number);
int get_bg_tile(int x, int y);

int create_sprite(int tile_number, int n_frames);
void set_sprite(int sprite_number, int x, int y);
void advance_sprite_frame(int sprite_number);
void set_sprite_flip(int sprite_number, int flip);
void clear_sprites();

