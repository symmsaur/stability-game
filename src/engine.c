#include <stdlib.h>
#include "engine.h"

#define SPRITE_CAP 64

struct sprite {
  int tile_number;
  int x;
  int y;
  int frame;
  int n_frames;
};

void draw_tile(int tile_number, int x, int y);
void draw_bg();
void draw_sprites();


static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *tiles;

static int *bg_tiles;
static struct sprite *sprites;

void init_engine() {
  srand(0);
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("mld59", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
      0);
  if (window == NULL) {
    printf("Failed to create window\n.");
    SDL_Quit();
  }

  renderer = SDL_CreateRenderer( window, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    printf("Failed to create renderer");
    SDL_Quit();
  }

  bg_tiles = malloc(sizeof(int) * BG_TILES_X * BG_TILES_Y);
  sprites = malloc(sizeof(struct sprite) * SPRITE_CAP);
  for(int i = 0; i < SPRITE_CAP; i++) {
    sprites[i].tile_number = -1;
  }
}

int load_assets() {
  tiles = IMG_LoadTexture(renderer, "../assets/tiles.png");
  if (tiles == NULL) return 1;
  else return 0;
}

int shutdown_engine() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  free(bg_tiles);
  return 0;
}

int render_frame() {
  frame_number++;
  SDL_RenderClear(renderer);
  draw_bg();
  draw_sprites();
  SDL_RenderPresent(renderer);
  return 0;
}

void set_bg_tile(int x, int y, int tile_number) {
  bg_tiles[y * BG_TILES_X + x] = tile_number;
}

int get_bg_tile(int x, int y)
{
  return bg_tiles[y * BG_TILES_X + x];
}

int create_sprite(int tile_number, int n_frames)
{
  static int next = 0;
  sprites[next].tile_number = tile_number;
  sprites[next].n_frames = n_frames;
  sprites[next].frame = 0;
  set_sprite(next, 0, 0);
  return next++;
}

void set_sprite(int sprite_number, int x, int y)
{
  sprites[sprite_number].x = x;
  sprites[sprite_number].y = y;
}

void advance_sprite_frame(int sprite_number){
  sprites[sprite_number].frame = (sprites[sprite_number].frame + 1) % 
    sprites[sprite_number].n_frames;
}

void draw_bg()
{
  for(int x = 0; x < BG_TILES_X; x++){
    for (int y = 0; y < BG_TILES_Y; y++){
      draw_tile(
          x * TILE_SIZE * PIXEL_FACTOR, 
          y * TILE_SIZE * PIXEL_FACTOR, 
          bg_tiles[y * BG_TILES_X + x]
          );
    }
  }
}

void draw_sprites()
{
  for (int i = 0; i < SPRITE_CAP; i++)
  {
    if (sprites[i].tile_number >= 0) {
      draw_tile(
          sprites[i].x,
          sprites[i].y,
          sprites[i].tile_number + sprites[i].frame
          );
    }
  }
}

void draw_tile(int x, int y, int tile_number) {
  SDL_Rect tile, target;

  tile.x = TILE_SIZE * (tile_number % TILES_X);
  tile.y = TILE_SIZE * (tile_number / TILES_X);
  tile.w = TILE_SIZE;
  tile.h = TILE_SIZE;

  target.x = x;
  target.y = y;
  target.w = TILE_SIZE * PIXEL_FACTOR;
  target.h = TILE_SIZE * PIXEL_FACTOR;

  SDL_RenderCopy(renderer, tiles, &tile, &target);
}
