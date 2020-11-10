//
// Created by Alexander Nathanail on 10/11/2020.
//

#include <stdlib.h>
#include <strings.h>
#include "data_proc.h"


GraphConnection** get_graph_from_connections(const Connection connections[], int num_connections, int graph_size) {
  GraphConnection **out = malloc(graph_size * sizeof(GraphConnection*));
  for (int i = 0; i < graph_size; i++) {
    out[i] = malloc(graph_size * sizeof(GraphConnection));
  }
  // Initialise graph with every station unconnected
  for (int i = 0; i < graph_size; i++) {
    for (int j = 0; j < graph_size; j++) {
      out[i][j].time = -1;
      out[i][j].line = -1;
    }
  }
  // Populate graph with connections
  for (int i = 0; i < num_connections; i++) {
    out[connections[i].station1][connections[i].station2].time = connections[i].time;
    out[connections[i].station1][connections[i].station2].line = connections[i].line;
    out[connections[i].station2][connections[i].station1].time = connections[i].time;
    out[connections[i].station2][connections[i].station1].line = connections[i].line;
  }
  return out;
}

PartialStation** get_stations_map_from_stations(const Station stations[], int num_stations, int station_arr_length, int max_name_length) {
  PartialStation** out = malloc(station_arr_length * sizeof(PartialStation*));
  for (int i = 0; i < station_arr_length; i++) {
    out[i] = malloc(sizeof(PartialStation));
    out[i]->name = calloc(max_name_length, sizeof(char));
  }
  for (int i = 0; i < num_stations; i++) {
    if (stations[i].id > 0) {
      strcpy(out[stations[i].id]->name, stations[i].name);
      out[stations[i].id]->zone = stations[i].zone;
    }
  }
  return out;
}

char** get_line_names_from_lines(const Line lines[], int num_lines, int line_arr_length, int max_name_length) {
  char **out = malloc(line_arr_length * sizeof(char*));
  for (int i = 0; i < line_arr_length; i++) {
    out[i] = calloc(max_name_length, sizeof(char));
  }
  for (int i = 0; i < num_lines; i++) {
    if (lines[i].line > 0) {
      strcpy(out[lines[i].line], lines[i].name);
    }
  }
  return out;
}
