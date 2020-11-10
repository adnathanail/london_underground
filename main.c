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

int get_next_closest_node(const int dist[MAX_STATION_ID], Queue remaining_stations);
void display_route(int origin, int destination, const int *distances_to_origin, const PathConnection paths[MAX_STATION_ID][MAX_STATION_ID]);
void dijkstra(int origin, int destination);

GraphConnection** graph;
PartialStation** stations_map;
char** line_names;

int main() {
  graph = get_graph_from_connections(CONNECTIONS, NUM_CONNECTIONS, MAX_STATION_ID + 1);
  stations_map = get_stations_map_from_stations(STATIONS, NUM_STATIONS, MAX_STATION_ID + 1, MAX_NAME_LENGTH);
  line_names = get_line_names_from_lines(LINES, NUM_LINES, MAX_LINE_ID + 1, MAX_NAME_LENGTH);

  dijkstra(145, 21);
  // ^ STP to Fulham Broadway

  return 0;
}

void dijkstra(int origin, int destination) {
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
                paths[u][i - 1].line = graph[v][u].line;  // Set the previous stations line
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

  display_route(origin, destination, distances_to_origin, paths);
}

int get_next_closest_node(const int dist[MAX_STATION_ID], Queue remaining_stations) {
  int closest_node = -1;
  int closes_node_distance = INT_MAX;
  int i = 0;
  while (remaining_stations.items[i] != -1 && i < MAX_STATION_ID) {
    if (dist[remaining_stations.items[i]] < closes_node_distance || closest_node == -1) {
      closest_node = remaining_stations.items[i];
      closes_node_distance = dist[remaining_stations.items[i]];
    }
    i++;
  }
  return closest_node;
}

void display_route(int origin, int destination, const int *distances_to_origin, const PathConnection paths[MAX_STATION_ID][MAX_STATION_ID]) {
  printf("%s to %s: %i minutes\n", stations_map[origin]->name, stations_map[destination]->name, distances_to_origin[destination]);
  puts("--------------------");
  int j = 0;
  int current_line = -1;
  double min_zone = 100;
  double max_zone = -1;
  int num_changes = 0;
  while (paths[destination][j].station_id != -1) {
    if (current_line != paths[destination][j].line && paths[destination][j].line != -1) {
      current_line = paths[destination][j].line;
      if (j == 0) {
        printf("Start on ");
      } else {
        num_changes += 1;
        printf("\t%s\n", stations_map[paths[destination][j].station_id]->name);
        printf("Change to ");
      }
      printf("%s\n", line_names[paths[destination][j].line]);
    }
    printf("\t%s\n", stations_map[paths[destination][j].station_id]->name);
    if (stations_map[paths[destination][j].station_id]->zone < min_zone) {
      min_zone = stations_map[paths[destination][j].station_id]->zone;
    }
    if (stations_map[paths[destination][j].station_id]->zone > max_zone) {
      max_zone = stations_map[paths[destination][j].station_id]->zone;
    }
    j++;
  }
  puts("--------------------");
  printf("Zones %.1f to %.1f\n", min_zone, max_zone);
  printf("%i changes\n", num_changes);
}