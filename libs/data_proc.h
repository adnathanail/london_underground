//
// Created by Alexander Nathanail on 10/11/2020.
//

#ifndef LONDON_UNDERGROUND_DATA_PROC_H
#define LONDON_UNDERGROUND_DATA_PROC_H

#include "data_types.h"

struct graph_connection {
  int time;
  int line;
};

typedef struct graph_connection GraphConnection;

GraphConnection** get_graph_from_connections(const Connection connections[], int num_connections, int graph_size);
PartialStation** get_stations_map_from_stations(const Station stations[], int station_arr_length, int max_name_length);
char** get_line_names_from_lines(const Line lines[], int line_arr_length, int max_name_length);

#endif //LONDON_UNDERGROUND_DATA_PROC_H
