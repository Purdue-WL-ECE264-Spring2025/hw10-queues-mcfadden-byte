#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
	insert_at_tail(&(q -> data), serialize(state));
}

struct game_state dequeue(struct queue *q) {
	struct game_state result = deserialize((q -> data).head -> value);

	remove_from_head(&(q -> data));

	return result;
}

int number_of_moves(struct game_state start) {
	

	/*struct game_state up = start;	
	struct game_state down = start;
	struct game_state left = start;
	struct game_state right = start;

	move_up(&up);
	move_down(&down);
	move_left(&left);
	move_right(&right);*/

	struct game_state udlr[4] = {start, start, start, start};
	move_up(udlr);
	move_down(udlr+1);
	move_left(udlr+2);
	move_right(udlr+3);

	//check if any are correct
	//if not, call self on each new one
	int counter = 1;
	int is_correct = 1;
	for (int i = 0; i < 4; i++){
		is_correct = 1;
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 4; k++){
				if (udlr[i].tiles[j][k] != counter && counter != 16){
					is_correct = 0;
					break;
				}
				counter++;
			}
		}
		if (is_correct != 0){
			return udlr[i].num_steps;
		}

	}

	return 0;
}
