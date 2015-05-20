#include <stdlib.h>
#include "engine.h"


static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *tiles;


int init_engine() {
  srand(0);
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("mld59", 0, 0, 640, 480, SDL_WINDOW_FULLSCREEN);
  renderer = SDL_CreateRenderer(
      window, 
      -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
      );
  
  tiles = IMG_LoadTexture(renderer, "tiles.png");
  if (tiles == NULL) 
  {
    printf("oops, no tiles");
  }

  if (window != NULL) return 0;
  else return 1;
}

int shutdown_engine() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  return 0;
}

int render_frame() {
  // Redraw once per second approx.
  static int frame = 0;
  frame++;
  if ((frame % 60) != 0) 
  {
    SDL_RenderPresent(renderer);
  }
  else
  {
    int tile_number = rand() % 64;
    SDL_Rect src;

    src.x = 16 * (tile_number % 8);
    src.y = 16 * (tile_number / 8);
    src.w = 16;
    src.h = 16;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tiles, &src, NULL);
    SDL_RenderPresent(renderer);
  }
  return 0;
}
