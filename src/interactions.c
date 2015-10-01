#include "interactions.h"
#include "game.h"
#include "collision.h"
#include "fireguy.h"
#include "solidgrunt.h"

void resolve_collisions() {
	int i = 0;
	fireguy *guy;
	solidgrunt *grunt;
	while ((guy = get_fireguy(i++)) != 0) {
		int j = 0;
		while ((grunt = get_solidgrunt(j++)) != 0) {
			if (actor_actor_collision(guy->actor_state, grunt->actor_state)) {
				kill_guy(guy);
			}
		}
	}

	int k = 0;
	actor_state *player_state = get_player_actor_state();
	while ((guy = get_fireguy(k++)) != 0) {
		if (actor_actor_collision(guy->actor_state, *player_state)) {
			player_pickup_guy(guy);
		}
	}
}