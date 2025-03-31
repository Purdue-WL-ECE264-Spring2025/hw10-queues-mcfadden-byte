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
	
	//look at the first thing in queue; if correct, return its num_moves
	//
	//If not correct, create four temp copies, execute different move on each, place each in back of queue
	//Advance to next item in queue

	//Set up the first thing in queue, which is the input grid
	struct queue que;
	struct queue * q = &que;
	struct list_node first; first.value = serialize(start); first.next = NULL;
	(q -> data).head = &first;
	int found = 0;
	int num_steps = 0;

	
	while (found == 0){
		struct game_state temp = dequeue(q);
		//printf("NUM STEPS: %d\n", temp.num_steps);

		//Check if first thing in queue is correct
		int equal = 1;
		int counter = 1;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				if (temp.tiles[i][j] != counter && counter != 16){
					equal = 0;
					break;
				}
				counter++;
			}
		}

		//If first thing in queue is not correct, create four copies, one for each move, and add them to the back of queue
		if (equal == 0){
			struct game_state udlr[4] = {temp, temp, temp, temp};
			move_up(udlr);
			move_down(udlr+1);
			move_left(udlr+2);
			move_right(udlr+3);

			for (int i = 0; i < 4; i++){
				enqueue(q, udlr[i]);
			}
		}else{
			//If first thing in queue is correct, record the number of steps
			found = 1;
			num_steps = temp.num_steps;
		}

	}

	return num_steps;
}
