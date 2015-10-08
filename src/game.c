#include "game.h"
#include "engine.h"
#include "level.h"
#include "collision.h"
#include "fireguy.h"
#include "solidgrunt.h"
#include "interactions.h"

// FLAGS
#define ON_GROUND 1

// MOVEMENT CONSTANTS
#define PLAYER_ACCELERATION 3
#define PLAYER_DECELERATION PLAYER_ACCELERATION
#define PLAYER_FRICTION 1
#define PLAYER_MAX_SPEED 32
#define PLAYER_JUMP_SPEED (-48)
#define PLAYER_JUMP_FRAMES 13
#define MAX_FALL_SPEED 88

#define THROW_SPEED_X 48
#define THROW_SPEED_Y 24

void player_tick();

struct player_state {
	actor_state actor_state;
	int vel_x;
	int vel_y;
	int sprite;
	int jmp_frames;
	fireguy *picked_up_guy;
	int enable_pickup;
	int state;
};

static struct player_state player;

void init_game() {
	init_fireguy();
	init_solidgrunt();
	global_frame_number = 0;
	clear_sprites();
	player.sprite = create_sprite(CHR_RUN_LEFT, CHR_RUN_LEFT_NUM);
	player.actor_state.x = SCREEN_WIDTH / 2;
	player.actor_state.y = SCREEN_HEIGHT / 2;
	player.vel_x = 0;
	player.vel_y = 0;
	player.jmp_frames = 0;
	player.state = 0;
	load_level("../assets/level1.lvl", false);
}

void set_player_pos(int x, int y) {
	player.actor_state.x = x;
	player.actor_state.y = y;
}

actor_state* get_player_actor_state() {
	return &player.actor_state;
}

void player_move(int dir) {
	if (dir > 0) {
		if (player.vel_x < 0) player.vel_x += PLAYER_DECELERATION;
		else  player.vel_x += PLAYER_ACCELERATION;

		if (player.vel_x >= PLAYER_MAX_SPEED) player.vel_x = PLAYER_MAX_SPEED;
	}
	if (dir < 0) {
		if (player.vel_x > 0) player.vel_x -= PLAYER_DECELERATION;
		else player.vel_x -= PLAYER_ACCELERATION;

		if (player.vel_x <= -PLAYER_MAX_SPEED) player.vel_x = -PLAYER_MAX_SPEED;
	}
}

void player_jump() {
	if (player.state & ON_GROUND) {
		player.jmp_frames = PLAYER_JUMP_FRAMES;
	}
	if (player.jmp_frames > 0)
	{
		player.vel_y = PLAYER_JUMP_SPEED;
	}
}

void player_end_jump() {
	player.jmp_frames = 0;
}

void tick() {
	tick_fireguys();
	tick_solidgrunts();
	player_tick();
	resolve_collisions();
	global_frame_number++;
}

void player_enable_pickup(int enable) {
	player.enable_pickup = enable;
}

void player_pickup_guy(fireguy *guy) {
	if (player.enable_pickup)
	{
		guy->move_state = picked_up;
		player.picked_up_guy = guy;
	}
}

void update_player_position() {
	int vel_x = player.vel_x / 8;
	int vel_y = player.vel_y / 8;
	int sgn_x = vel_x > 0 ? 1 : -1;
	int sgn_y = vel_y > 0 ? 1 : -1;
	int p_x = player.actor_state.x;
	int p_y = player.actor_state.y;

	// We will move pixel by pixel and check for collisions along the way.
	for (int dx = sgn_x; abs(dx) <= abs(vel_x); dx += sgn_x) {
		if (actor_level_collision(p_x + dx, p_y)) {
			player.vel_x = 0;
			break;
		}
		else {
			player.actor_state.x += sgn_x;
		}
	}
	for (int dy = sgn_y; abs(dy) <= abs(vel_y); dy += sgn_y) {
		if (actor_level_collision(player.actor_state.x, p_y + dy)) {
			if (vel_y > 0) {
				player.state |= ON_GROUND;
			}
			else {
				// Cancel any jump if we hit our head.
				player.jmp_frames = 0;
			}
			player.vel_y = 0;
			break;
		}
		else {
			player.actor_state.y += sgn_y;
		}
	}
}

int update_actor_position(actor_state *actor) {
	int ret = 0;
	int vel_x = actor->vel_x / 8;
	int vel_y = actor->vel_y / 8;
	int sgn_x = vel_x > 0 ? 1 : -1;
	int sgn_y = vel_y > 0 ? 1 : -1;
	int p_x = actor->x;
	int p_y = actor->y;

	// We will move pixel by pixel and check for collisions along the way.
	for (int dx = sgn_x; abs(dx) <= abs(vel_x); dx += sgn_x) {
		if (actor_level_collision(p_x + dx, p_y)) {
			if (sgn_x > 0) ret |= COLLISION_RIGHT_FLAG;
			else ret |= COLLISION_LEFT_FLAG;
			break;
		}
		else {
			actor->x += sgn_x;
		}
	}
	for (int dy = sgn_y; abs(dy) <= abs(vel_y); dy += sgn_y) {
		if (actor_level_collision(actor->x, p_y + dy)) {
			if (sgn_y > 0) {
				ret |= COLLISION_BOTTOM_FLAG;
			}
			else {
				ret |= COLLISION_TOP_FLAG;
			}
			break;
		}
		else {
			actor->y += sgn_y;
		}
	}
	return ret;
}

void player_tick() {
	if (!player.enable_pickup && player.picked_up_guy != NULL) {
		player.picked_up_guy->move_state = flying;
		player.picked_up_guy->actor_state.vel_x = player.vel_x + ((player.vel_x > 0) - (player.vel_x < 0)) * THROW_SPEED_X;
		player.picked_up_guy->actor_state.vel_y = player.vel_y - THROW_SPEED_Y;
		player.picked_up_guy = NULL;
	}

	static int adv_player_frame = 50;
	player.state = 0;

	// Falling and stuff!
	if (player.jmp_frames == 0) player.vel_y += GRAVITATIONAL_ACCELERATION;
	if (player.vel_y > MAX_FALL_SPEED) player.vel_y = MAX_FALL_SPEED;

	if (player.jmp_frames > 0) player.jmp_frames--;

	update_player_position();

	// Decelerate player
	if (player.vel_x > 0) player.vel_x -= PLAYER_FRICTION;
	else if (player.vel_x < 0) player.vel_x += PLAYER_FRICTION;

	// Animate player sprite depending on how fast the player is moving.
	set_sprite(player.sprite, player.actor_state.x, player.actor_state.y);
	if (adv_player_frame > 0) {
		adv_player_frame -= (10 * abs(player.vel_x)) / (PLAYER_MAX_SPEED);
	} 
	else {
		advance_sprite_frame(player.sprite);
		adv_player_frame = 50;
	}
	
	if (player.vel_x < 0)
	{
		set_sprite_flip(player.sprite, SPRITE_FLIP_X);
		if (player.picked_up_guy != NULL)
		{
			update_picked_up_guy(
				player.picked_up_guy,
				player.actor_state.x,
				player.actor_state.y,
				SPRITE_FLIP_X
				);
		}
	}
	else if (player.vel_x >= 0)
	{
		set_sprite_flip(player.sprite, 0);
		if (player.picked_up_guy != NULL)
		{
			update_picked_up_guy(
				player.picked_up_guy,
				player.actor_state.x,
				player.actor_state.y,
				0
				);
		}
	}
}
