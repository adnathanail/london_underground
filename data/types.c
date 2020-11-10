//
// Created by Alexander Nathanail on 09/11/2020.
//

struct station {
  int id;
  double latitude;
  double longitude;
  char name[1000];
  double zone;
  int total_lines;
  int rail;
};

typedef struct station Station;

struct connection {
  int station1;
  int station2;
  int line;
  int time;
};

typedef struct connection Connection;

struct line {
  int line;
  char name[1000];
  char colour[1000];
  char stripe[1000];
};

typedef struct line Line;