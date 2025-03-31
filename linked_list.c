#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
	struct list_node * result = malloc(sizeof(struct list_node));
	result -> value = value; result -> next = NULL;
	return result;
}

void insert_at_head(struct linked_list *list, size_t value){
	struct list_node * node = new_node(value);
	node -> next = list -> head;
	list -> head = node;
}

void insert_at_tail(struct linked_list *list, size_t value) {
	if (list -> head == NULL){
		list -> head = new_node(value);
	}else{
		struct list_node * last = list -> head;
		while (last -> next != NULL){
			last = last -> next;
		}
		last -> next = new_node(value);
	}
}

size_t remove_from_head(struct linked_list *list) {
	size_t result = list -> head -> value;
	struct list_node * temp = list -> head;
	list -> head = list -> head -> next;
	free(temp);
	return result;
}

size_t remove_from_tail(struct linked_list *list) {
	size_t result;
	if (list -> head -> next == NULL){
		result = list -> head -> value;
		free(list -> head);
		list -> head = NULL;
	}else{
		struct list_node * last = list -> head;
		while(last -> next -> next != NULL){
			last = last -> next;
		}

		result = last -> next -> value;
		free(last -> next);
		last -> next = NULL;
	}

	return result;
}

void free_list(struct linked_list list) {
	if (list.head != NULL){
		struct list_node * temp = list.head;
		while (list.head -> next != NULL){
			list.head = list.head -> next;
			free(temp);
			temp = list.head;
		}
		free(temp);
	}
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
