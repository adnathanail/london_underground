//
// Created by Alexander Nathanail on 10/11/2020.
//

#include "data_structures.h"

void pop(Queue* queue, int val) {
  int shifting = 0;
  for (int i = 0; i < MAX_STATION_ID; i++) {
    if (queue->items[i] == val) {
      shifting = 1;
    }
    if (shifting) {
      queue->items[i] = queue->items[i + 1];
    }
  }
  queue->items[MAX_STATION_ID - 1] = -1;
}