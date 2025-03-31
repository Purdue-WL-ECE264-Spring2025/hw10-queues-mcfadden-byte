#include "queue.h"
#include "tile_game.h"
#include <string.h>

void enqueue(struct queue *q, struct game_state state) {
	insert_at_head(&(q -> data), serialize(state));
}

struct game_state dequeue(struct queue *q) {
	struct game_state result = deserialize(remove_from_tail(&(q -> data)));

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
	(q -> data).head = NULL;
	enqueue(q, start);
	int found = 0;
	int num_steps = 0;
	int que_length = 1;
	//size_t prev[500000] = {0};
	//int index = 0;
	int goal[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};

	
	while (found == 0){
		struct game_state temp = dequeue(q);
		//prev[index] = serialize(temp);
		//index++;
		que_length--;
		//printf("NUM STEPS: %d\n", temp.num_steps);
		//printf("QUE LENGTH: %d\n", que_length);

		//Check if first thing in queue is correct
		int equal = 1;
		/*if (memcmp(temp.tiles, goal, sizeof(goal)) == 0){
			found = 1;
			num_steps = temp.num_steps;
			break;
		}*/
		for (int i = 0; i < 4 && equal == 1; i++){
			for (int j = 0; j < 4 && equal == 1; j++){
				//printf("%02d ", temp.tiles[i][j]);
				if (temp.tiles[i][j] != goal[i][j]){
					equal = 0;
				}
			}
			//printf("\n");
		}
		//printf("\n");

		//If first thing in queue is not correct, create four copies, one for each move, and add them to the back of queue
		if (equal == 0){
			struct game_state udlr[4] = {temp, temp, temp, temp};
			move_up(udlr);
			move_down(udlr+1);
			move_left(udlr+2);
			move_right(udlr+3);
			
			//printf("NUM ENQUEUED: ");
			for (int i = 0; i < 4; i++){
				//Check if already encountered
				int copy = 1;
				if (udlr[i].num_steps == temp.num_steps + 1){
					copy = 0;
				}
				//For everything in the queue...
				if ((q->data).head != NULL){
					struct list_node * curr = (q->data).head;
					while (curr -> next != NULL && copy == 0){
						//Check if equal to compare
						int copy_of_compare = 1;
						struct game_state compare = deserialize(curr -> value);
						for (int j = 0; j < 4 && copy_of_compare == 1; j++){
							for (int k = 0; k < 4 && copy_of_compare == 1; k++){
								if (udlr[i].tiles[j][k] != compare.tiles[j][k]){
									copy_of_compare = 0;
								}
							}
						}
						if (copy_of_compare == 1){
							copy = 1;
						}
						curr = curr -> next;
					}
				}


				if (udlr[i].num_steps == temp.num_steps + 1 && copy == 0){
					enqueue(q, udlr[i]);
					que_length++;
				}
			}
			//printf("\n");
		}else{
			//If first thing in queue is correct, record the number of steps
			found = 1;
			num_steps = temp.num_steps;
		}

	}

	free_list(q -> data);

	return num_steps;
}
