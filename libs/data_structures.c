//
// Created by Alexander Nathanail on 10/11/2020.
//

#include <stdlib.h>

#include "data_structures.h"

void queue_init(Queue* queue, int length) {
  queue->length = length;
  queue->items = malloc(length * sizeof(int));
}

void queue_pop(Queue* queue, int val) {
  int shifting = 0;
  for (int i = 0; i < queue->length; i++) {
    if (queue->items[i] == val) {
      shifting = 1;
    }
    if (shifting) {
      queue->items[i] = queue->items[i + 1];
    }
  }
  queue->items[queue->length - 1] = -1;
}