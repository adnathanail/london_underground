//
// Created by Alexander Nathanail on 10/11/2020.
//

#ifndef LONDON_UNDERGROUND_DATA_PROC_H
#define LONDON_UNDERGROUND_DATA_PROC_H

#endif //LONDON_UNDERGROUND_DATA_PROC_H

#include "data.h"

struct graph_connection {
  int time;
  int line;
};

typedef struct graph_connection GraphConnection;

extern GraphConnection** get_graph_from_connections(const Connection connections[]);
char** get_station_names_from_stations(const Station stations[]);
char** get_line_names_from_lines(const Line lines[]);