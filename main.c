#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <strings.h>
#include "data/data.h"

struct queue {
  int items[MAX_STATION_ID];
};

typedef struct queue Queue;

struct graph_connection {
  int time;
  int line;
};

typedef struct graph_connection GraphConnection;

struct path_connection {
  int station_id;
  int line;
};

typedef struct path_connection PathConnection;

char** station_names;
char** line_names;

int get_next_closest_node(const int dist[MAX_STATION_ID], Queue Q) {
  int closest_node = -1;
  int closes_node_distance = INT_MAX;
  int i = 0;
  while (Q.items[i] != -1 && i < MAX_STATION_ID) {
    if (dist[Q.items[i]] < closes_node_distance || closest_node == -1) {
      closest_node = Q.items[i];
      closes_node_distance = dist[Q.items[i]];
    }
    i++;
  }
  return closest_node;
}

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

void display_results(int origin, int destination, const int *dist, const PathConnection paths[MAX_STATION_ID][MAX_STATION_ID]) {
  for (int i = 0; i < MAX_STATION_ID; i++) {
    if (i == destination) {
      printf("%s to %s: %i via ", station_names[origin], station_names[i], dist[i]);
      int j = 0;
      int current_line = -1;
      while (paths[i][j].station_id != -1) {
        if (current_line != paths[i][j].line) {
          current_line = paths[i][j].line;
          printf("%s\n", line_names[paths[i][j].line]);
        }
        printf("\t%s\n", station_names[paths[i][j].station_id]);
        j++;
      }
      break;
    }
  }
}

void dijkstra(GraphConnection** graph, int origin, int destination) {
  // Dijkstra implementation based off https://brilliant.org/wiki/dijkstras-short-path-finder/
  int distances_to_origin[MAX_STATION_ID];
  for (int i = 0; i < MAX_STATION_ID; i++) {
    distances_to_origin[i] = INT_MAX;
  }
  distances_to_origin[origin] = 0;

  Queue remaining_stations;
  for (int i = 0; i < MAX_STATION_ID; i++) {
    remaining_stations.items[i] = i;
  }
  // Array of arrays of the stations visited in each stations path from the origin
  PathConnection paths[MAX_STATION_ID][MAX_STATION_ID];
  for (int i = 0; i < MAX_STATION_ID; i++) {
    for (int j = 0; j < MAX_STATION_ID; j++) {
      paths[i][j].station_id = -1;
      paths[i][j].line = -1;
    }
  }
  paths[origin][0].station_id = origin;
  // Dijkstra
  while (remaining_stations.items[0] != -1) {
    int v = get_next_closest_node(distances_to_origin, remaining_stations);
    pop(&remaining_stations, v);
    for (int u = 0; u < MAX_STATION_ID; u++) {
      if (graph[v][u].time != -1) {
        if ((distances_to_origin[v] + graph[v][u].time) < distances_to_origin[u]) {
          distances_to_origin[u] = distances_to_origin[v] + graph[v][u].time;
          if (paths[v][0].station_id != -1) {
            for (int i = 0; i < MAX_STATION_ID; i++) {
              if (paths[v][i].station_id != -1) {  // Copy v to u
                paths[u][i] = paths[v][i];
              } else if (paths[v][i - 1].station_id != -1) {  // Add u to the end of it's own path
                paths[u][i].station_id = u;
                paths[u][i].line = graph[v][u].line;
              } else {  // Clear any remnants of old paths
                paths[u][i].station_id = -1;
                paths[u][i].line = -1;
              }
            }
          }
        }
      }
    }
  }
  display_results(origin, destination, distances_to_origin, paths);
}

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

void get_station_names_from_stations(const Station stations[]) {
  int arr_len = MAX_STATION_ID + 1;  // If the max ID is 10 we need an array of length 11
  station_names = malloc(arr_len * sizeof(char*));
  for (int i = 0; i < arr_len; i++) {
    station_names[i] = malloc(MAX_NAME_LENGTH * sizeof(char));
    strcpy(station_names[i], "");
  }
  for (int i = 0; i < arr_len; i++) {
    if (stations[i].id > 0) {
      strcpy(station_names[stations[i].id], stations[i].name);
    }
  }
}

void get_line_names_from_lines(const Line lines[]) {
  int arr_len = NUM_LINES + 1;  // If the max ID is 10 we need an array of length 11
  line_names = malloc(arr_len * sizeof(char*));
  for (int i = 0; i < arr_len; i++) {
    line_names[i] = malloc(MAX_NAME_LENGTH * sizeof(char));
    strcpy(line_names[i], "");
  }
  for (int i = 0; i < arr_len; i++) {
    if (lines[i].line > 0) {
      strcpy(line_names[lines[i].line], lines[i].name);
    }
  }
}

int main() {
  GraphConnection** graph = get_graph_from_connections(CONNECTIONS);
  get_station_names_from_stations(STATIONS);
  get_line_names_from_lines(LINES);

  dijkstra(graph, 145, 96);
  // ^ STP to Fulham Broadway

  return 0;
}
