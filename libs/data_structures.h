//
// Created by Alexander Nathanail on 10/11/2020.
//

#ifndef LONDON_UNDERGROUND_DATA_STRUCTURES_H
#define LONDON_UNDERGROUND_DATA_STRUCTURES_H

#include "../data/data.h"

struct queue {
  int items[MAX_STATION_ID];
};

typedef struct queue Queue;

void pop(Queue* queue, int val);

#endif //LONDON_UNDERGROUND_DATA_STRUCTURES_H
