#include "main.h"

int main()
{
  printf("Starting...\n");
  init_engine();
  
  // TODO: Extract input loop
  while(1) {
    render_frame();
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) break;
    }
  }
  shutdown_engine();

  return 0;
}

