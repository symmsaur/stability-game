#pragma once
#include "game.h"

typedef struct {
	actor_state actor_state;
	int sprite;
	move_state move_state;
} solidgrunt;

void create_solidgrunt(int x, int y);
void init_solidgrunt();
solidgrunt* get_solidgrunt(int i);
void tick_solidgrunts();
void kill_grunt(solidgrunt *grunt);