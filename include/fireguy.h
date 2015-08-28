#pragma once
#include "game.h"

typedef enum {
	left, right
} move_state;

typedef struct {
	actor_state actor_state;
	int sprite;
	move_state move_state;
} fireguy;

int create_fireguy(int x, int y);
void init_fireguy();
void tick_fireguys();