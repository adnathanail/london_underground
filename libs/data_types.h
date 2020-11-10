//
// Created by Alexander Nathanail on 10/11/2020.
//

#ifndef LONDON_UNDERGROUND_DATA_TYPES_H
#define LONDON_UNDERGROUND_DATA_TYPES_H

#define MAX_NAME_LENGTH 100

struct station {
  int id;
  double latitude;
  double longitude;
  char name[MAX_NAME_LENGTH];
  double zone;
  int total_lines;
  int rail;
};

typedef struct station Station;

struct partial_station {
  char* name;
  double zone;
};

typedef struct partial_station PartialStation;

struct connection {
  int station1;
  int station2;
  int line;
  int time;
};

typedef struct connection Connection;

struct line {
  int line;
  char name[MAX_NAME_LENGTH];
  char colour[MAX_NAME_LENGTH];
};

typedef struct line Line;

#endif //LONDON_UNDERGROUND_DATA_TYPES_H
