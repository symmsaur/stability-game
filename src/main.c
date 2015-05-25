#include "main.h"

const Uint8 *key_state;

void print_stats();

int main()
{
  int res;
  printf("Starting...\n");
  init_engine();
  res = load_assets();
  if (res != 0)
  {
    printf("Failed loading assets");
    SDL_Quit();
  }

  init_game();

  key_state = SDL_GetKeyboardState(NULL);
  
  printf("Ready\n");
  // TODO: Extract input loop
  while(1) {
    render_frame();
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) break;
    }
    if (key_state[SDL_SCANCODE_SPACE]) {
      set_bg_tile(
          rand() % BG_TILES_X,
          rand() % BG_TILES_Y,
          rand() % (TILES_X * TILES_Y)
          );
    }
    if (key_state[SDL_SCANCODE_LEFT]) {
      move_player(-1);
    }
    if (key_state[SDL_SCANCODE_RIGHT]) {
      move_player(1);
    }
  }
  printf("Shutting down...\n");
  shutdown_engine();

  print_stats();

  SDL_Quit();
}

void print_stats(){
  printf("bg_tiles_x: %d\n", BG_TILES_X);
  printf("bg_tiles_y: %d\n", BG_TILES_Y);
}

