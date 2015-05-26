#include "SDL.h"
#include "SDL_image.h"

#include "tiles.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PIXEL_FACTOR 2

#define BG_TILES_X SCREEN_WIDTH / (TILE_SIZE * PIXEL_FACTOR)
#define BG_TILES_Y SCREEN_HEIGHT / (TILE_SIZE * PIXEL_FACTOR)

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

