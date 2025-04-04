#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
  // write this too
  struct list_node * n = malloc(sizeof(struct list_node));
  n->value = value;
  n->next = NULL;
  return n;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node * p = new_node(value);
  p->next = list->head;
  // p = list->head;
  list->head = p;
} //checked this function

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node * p = new_node(value);// check slide 118 of 20250304linkedlist
  struct list_node * q = list->head;
  if(q==NULL){return;} // probably not necessary
  while(p->next!=NULL){
    p=p->next;
  }
  p->next = q;
}

size_t remove_from_head(struct linked_list *list) { 
  struct list_node * p = list->head;
  size_t value = p->value;
  list->head = p->next;
  free(p); 
  return value;
}

size_t remove_from_tail(struct linked_list *list) {
  struct list_node * p = list->head;
  if(p->next==NULL){
    size_t val = p->value;
    free(p);
    list->head= NULL;
    return val;
  }
  while (p->next->next != NULL){
    p = p->next;
  }
  size_t value = p->next->value;
  free(p->next);
  p->next = NULL;
  return value;
}

void free_list(struct linked_list list) { 
  struct list_node * p = list.head;
  while (list.head != NULL){
    list.head = p->next;
    free(p);
    p = list.head;
    // p->next = p->next->next;
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
