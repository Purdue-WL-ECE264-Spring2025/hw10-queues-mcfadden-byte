#include "queue.h"
#include "tile_game.h"

//void print_q(struct queue *);

void enqueue(struct queue *q, struct game_state state) {
	insert_at_head(&(q -> data), serialize(state));
}

struct game_state dequeue(struct queue *q) {
	struct game_state result = deserialize(remove_from_tail(&(q -> data)));

	return result;
}

/*void print_q(struct queue * q){
	struct list_node * curr = (q -> data).head;
	printf("QUE START:\n");
	do{
		struct game_state state = deserialize(curr -> value);
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				printf("%d ", state.tiles[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		curr = curr -> next;
	}while (curr != NULL);
}*/


int number_of_moves(struct game_state start) {
	
	//look at the first thing in queue; if correct, return its num_moves
	//
	//If not correct, create four temp copies, execute different move on each, place each in back of queue
	//Advance to next item in queue

	//Set up the first thing in queue, which is the input grid
	struct queue que;
	struct queue * q = &que;
	(q -> data).head = NULL;
	//struct list_node * first = malloc(sizeof(struct list_node));
	//first -> value = serialize(start); first -> next = NULL;
	//(q -> data).head = first;
	enqueue(q, start);
	int found = 0;
	int num_steps = 0;
	int que_length = 1;

	
	while (found == 0){
		struct game_state temp = dequeue(q);
		que_length--;
		//printf("NUM STEPS: %d\n", temp.num_steps);
		//printf("QUE LENGTH: %d\n", que_length);

		//Check if first thing in queue is correct
		int equal = 1;
		int counter = 1;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				//printf("%02d ", temp.tiles[i][j]);
				if (temp.tiles[i][j] != counter && counter != 16){
					equal = 0;
				}
				counter++;
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
			
			for (int i = 0; i < 4; i++){
				if (udlr[i].num_steps == temp.num_steps + 1){
					enqueue(q, udlr[i]);
				}
				/*if (udlr[i].num_steps == 1){
					printf("NUM_STEPS = 1 HAS BEEN ADDED TO QUE! MOVE WAS: %d\n", i);
				}*/
			}
			que_length += 4;
		}else{
			//If first thing in queue is correct, record the number of steps
			found = 1;
			num_steps = temp.num_steps;
		}

	}

	free_list(q -> data);

	return num_steps;
}
