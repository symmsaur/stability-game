#include "main.h"
#include "editor.h"
#include "engine.h"
#include "level.h"

const Uint8 *key_state;

static int current_tile = 0;

void set_tile();
void update_current_tile(char i);

void init_editor(){
  printf("Initing editor\n");
  load_level("../assets/level1.lvl", true);
  printf("Level loaded\n");
}

void editor_loop(){
  int mouse_x, mouse_y;
  key_state = SDL_GetKeyboardState(NULL);
  
  printf("Ready\n");
  while(1) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) break;
    }
    if (SDL_GetMouseState(&mouse_x, &mouse_y) & SDL_BUTTON_LEFT){
      set_tile(mouse_x, mouse_y);
    }
    if (key_state[SDL_SCANCODE_Q]) break;

    if (key_state[SDL_SCANCODE_1]) update_current_tile('1');
    if (key_state[SDL_SCANCODE_2]) update_current_tile('2');
    if (key_state[SDL_SCANCODE_3]) update_current_tile('3');
    if (key_state[SDL_SCANCODE_4]) update_current_tile('4');
    if (key_state[SDL_SCANCODE_5]) update_current_tile('5');
    if (key_state[SDL_SCANCODE_6]) update_current_tile('6');
    if (key_state[SDL_SCANCODE_7]) update_current_tile('7');
    if (key_state[SDL_SCANCODE_8]) update_current_tile('8');
    if (key_state[SDL_SCANCODE_A]) update_current_tile('a');
    if (key_state[SDL_SCANCODE_B]) update_current_tile('b');
    if (key_state[SDL_SCANCODE_C]) update_current_tile('c');
    if (key_state[SDL_SCANCODE_D]) update_current_tile('d');
    if (key_state[SDL_SCANCODE_E]) update_current_tile('e');
    if (key_state[SDL_SCANCODE_F]) update_current_tile('f');
    if (key_state[SDL_SCANCODE_G]) update_current_tile('g');
    if (key_state[SDL_SCANCODE_H]) update_current_tile('h');

	if (key_state[SDL_SCANCODE_S]) {
		save_level("../assets/level1.lvl");
		printf("level saved.");
	}

    render_frame();
  }
}

void set_tile(int x, int y) {
  int tile_x, tile_y;
  tile_x = x / (TILE_SIZE * PIXEL_FACTOR);
  tile_y = y / (TILE_SIZE * PIXEL_FACTOR);
  set_bg_tile(tile_x, tile_y, current_tile);
}

void update_current_tile(char input){
  if (input >= '1' && input <= '8') {
    int n = input - '1';
    int diff = n - current_tile % 8;
    current_tile += diff;
  }
  else if (input >= 'a' && input <= 'h'){
    int x = current_tile % 8;
    int y = input - 'a';
    current_tile = y * TILES_Y + x;
  }
}

