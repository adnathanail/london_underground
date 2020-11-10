//
// Created by Alexander Nathanail on 10/11/2020.
//

#ifndef LONDON_UNDERGROUND_DATA_STRUCTURES_H
#define LONDON_UNDERGROUND_DATA_STRUCTURES_H

struct queue {
  int* items;
  int length;
};

typedef struct queue Queue;

void queue_init(Queue* queue, int length);
void queue_pop(Queue* queue, int val);

#endif //LONDON_UNDERGROUND_DATA_STRUCTURES_H
