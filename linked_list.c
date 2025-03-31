#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
	struct list_node * result = malloc(sizeof(struct list_node));
	result -> value = value; result -> next = NULL;
	return result;
}

void insert_at_head(struct linked_list *list, size_t value) {
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
	list -> head = list -> head -> next;
	return result;
}

size_t remove_from_tail(struct linked_list *list) {
	size_t result;

	while(list -> head -> next -> next != NULL){
		list -> head = list -> head -> next;
	}

	result = list -> head -> next -> value;
	free(list -> head -> next);
	list -> head -> next = NULL;

	return result;
}

void free_list(struct linked_list list) {}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
