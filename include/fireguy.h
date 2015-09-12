#pragma once
#include "game.h"

typedef struct {
	actor_state actor_state;
	int sprite;
	move_state move_state;
} fireguy;

void create_fireguy(int x, int y);
void init_fireguy();
void tick_fireguys();