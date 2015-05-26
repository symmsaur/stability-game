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
  while(1) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) break;
    }
    if (key_state[SDL_SCANCODE_LEFT]) {
      player_move(-1);
    }
    if (key_state[SDL_SCANCODE_RIGHT]) {
      player_move(1);
    }
    if (key_state[SDL_SCANCODE_SPACE]) {
      player_jump();
    }
    tick();
    render_frame();
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

