#include <stdio.h>
#include <limits.h>

#include "data/data.h"
#include "libs/data_proc.h"
#include "libs/data_structures.h"

struct path_connection {
  int station_id;
  int line;
};

typedef struct path_connection PathConnection;

int get_next_closest_node(const int dist[MAX_STATION_ID], Queue Q);
void display_results(int origin, int destination, const int *dist, const PathConnection paths[MAX_STATION_ID][MAX_STATION_ID]);
void dijkstra(GraphConnection** graph, int origin, int destination);

char** station_names;
char** line_names;

int main() {
  GraphConnection** graph = get_graph_from_connections(CONNECTIONS, NUM_CONNECTIONS, MAX_STATION_ID + 1);
  station_names = get_station_names_from_stations(STATIONS, MAX_STATION_ID + 1, MAX_NAME_LENGTH);
  line_names = get_line_names_from_lines(LINES, NUM_LINES + 1, MAX_NAME_LENGTH);

  dijkstra(graph, 145, 96);
  // ^ STP to Fulham Broadway

  return 0;
}

void dijkstra(GraphConnection** graph, int origin, int destination) {
  // Dijkstra implementation based off https://brilliant.org/wiki/dijkstras-short-path-finder/

  int distances_to_origin[MAX_STATION_ID];
  for (int i = 0; i < MAX_STATION_ID; i++) {
    distances_to_origin[i] = INT_MAX;
  }
  distances_to_origin[origin] = 0;

  Queue remaining_stations;
  queue_init(&remaining_stations, MAX_STATION_ID);
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
  paths[origin][0].station_id = origin;  // The origin starts off with a path to itself

  // Dijkstra
  while (remaining_stations.items[0] != -1) {
    int v = get_next_closest_node(distances_to_origin, remaining_stations);
    queue_pop(&remaining_stations, v);
    for (int u = 0; u < MAX_STATION_ID; u++) {
      if (graph[v][u].time != -1) {
        if ((distances_to_origin[v] + graph[v][u].time) < distances_to_origin[u]) {
          distances_to_origin[u] = distances_to_origin[v] + graph[v][u].time;
          if (paths[v][0].station_id != -1) {
            // If v has a path, copy it to u and add u to the end
            for (int i = 0; i < MAX_STATION_ID; i++) {
              if (paths[v][i].station_id != -1) {
                paths[u][i] = paths[v][i];
              } else if (paths[v][i - 1].station_id != -1) {
                paths[u][i].station_id = u;
                paths[u][i].line = graph[v][u].line;
              } else {
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

void display_results(int origin, int destination, const int *dist, const PathConnection paths[MAX_STATION_ID][MAX_STATION_ID]) {
  for (int i = 0; i < MAX_STATION_ID; i++) {
    if (i == destination) {
      printf("%s to %s: %i minutes\n", station_names[origin], station_names[i], dist[i]);
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