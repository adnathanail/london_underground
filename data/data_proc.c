//
// Created by Alexander Nathanail on 10/11/2020.
//

#include <stdlib.h>
#include <strings.h>
#include "data_proc.h"


GraphConnection** get_graph_from_connections(const Connection connections[]) {
  int arr_len = MAX_STATION_ID + 1;  // If the max ID is 10 we need an array of length 11
  GraphConnection **out = malloc(arr_len * sizeof(GraphConnection*));
  for (int i = 0; i < arr_len; i++) {
    out[i] = malloc(arr_len * sizeof(GraphConnection));
  }
  // Initialise graph with every station unconnected
  for (int i = 0; i < arr_len; i++) {
    for (int j = 0; j < arr_len; j++) {
      out[i][j].time = -1;
      out[i][j].line = -1;
    }
  }
  // Populate graph with connections
  for (int i = 0; i < NUM_CONNECTIONS; i++) {
    out[connections[i].station1][connections[i].station2].time = connections[i].time;
    out[connections[i].station1][connections[i].station2].line = connections[i].line;
    out[connections[i].station2][connections[i].station1].time = connections[i].time;
    out[connections[i].station2][connections[i].station1].line = connections[i].line;
  }
  return out;
}

char** get_station_names_from_stations(const Station stations[]) {
  int arr_len = MAX_STATION_ID + 1;  // If the max ID is 10 we need an array of length 11
  char **out = malloc(arr_len * sizeof(char*));
  for (int i = 0; i < arr_len; i++) {
    out[i] = malloc(MAX_NAME_LENGTH * sizeof(char));
    strcpy(out[i], "");
  }
  for (int i = 0; i < arr_len; i++) {
    if (stations[i].id > 0) {
      strcpy(out[stations[i].id], stations[i].name);
    }
  }
  return out;
}

char** get_line_names_from_lines(const Line lines[]) {
  int arr_len = NUM_LINES + 1;  // If the max ID is 10 we need an array of length 11
  char **out = malloc(arr_len * sizeof(char*));
  for (int i = 0; i < arr_len; i++) {
    out[i] = malloc(MAX_NAME_LENGTH * sizeof(char));
    strcpy(out[i], "");
  }
  for (int i = 0; i < arr_len; i++) {
    if (lines[i].line > 0) {
      strcpy(out[lines[i].line], lines[i].name);
    }
  }
  return out;
}
