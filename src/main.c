#include "main.h"

//#define EDITOR

const Uint8 *key_state;

void print_stats();
int command_args(int argc, const char *argv[]);

int main(int argc, const char *argv[]) {
  int res;
  printf("Starting...\n");
  init_engine();
  res = load_assets();
  if (res != 0)
  {
    printf("Failed loading assets");
    SDL_Quit();
  }

#ifdef EDITOR
  init_editor();
  editor_loop();
#else
  init_game();
#endif


  key_state = SDL_GetKeyboardState(NULL);
  
  printf("Ready\n");
  while(1) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) break;
    }
    if (key_state[SDL_SCANCODE_ESCAPE]) break;
    if (key_state[SDL_SCANCODE_LEFT]) {
      player_move(-1);
    }
    if (key_state[SDL_SCANCODE_RIGHT]) {
      player_move(1);
    }
    if (key_state[SDL_SCANCODE_SPACE]) {
      player_jump();
    }
    else {
      player_end_jump();
    }

    tick();
    render_frame();
  }
  printf("Shutting down...\n");
  shutdown_engine();

  print_stats();

  SDL_Quit();
  return 0;
}

// Windows support
int wmain() {
	return main(0, NULL);
}

void print_stats(){
  printf("bg_tiles_x: %d\n", BG_TILES_X);
  printf("bg_tiles_y: %d\n", BG_TILES_Y);
}

int command_args(int argc, const char *argv[]) {
  int flags = 0;
  for (int i = 0; i < argc ; i++) {
    // strcmp is a comparer, returns 0 for match.
    if (strcmp("-e", argv[i]) == 0) flags |= CMD_ARG_EDITOR;
  }
  return flags;
}

