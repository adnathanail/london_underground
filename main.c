#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "data/data.h"

struct queue {
  int items[MAX_STATION_ID];
};

typedef struct queue Queue;

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

void pop(Queue queue, int val) {
  int shifting = 0;
  for (int i = 0; i < MAX_STATION_ID; i++) {
    if (queue.items[i] == val) {
      shifting = 1;
    }
    if (shifting) {
      queue.items[i] = queue.items[i + 1];
    }
  }
  queue.items[MAX_STATION_ID - 1] = -1;
}

void dijkstra(int** graph, int origin) {
  // Dijkstra implementation based off https://brilliant.org/wiki/dijkstras-short-path-finder/
  // Array of distances from all stations to origin
  int dist[MAX_STATION_ID];
  for (int i = 0; i < MAX_STATION_ID; i++) {
    dist[i] = INT_MAX;
  }
  // Queue of stations to be worked through
  dist[origin] = 0;
  Queue Q;
  for (int i = 0; i < MAX_STATION_ID; i++) {
    Q.items[i] = i;
  }
  while (Q.items[0] != -1) {
    int v = get_next_closest_node(dist, Q);
    pop(Q, v);
    for (int u = 0; u < MAX_STATION_ID; u++) {
      if (graph[v][u] != -1) {
        if ((dist[v] + graph[v][u]) < dist[u]) {
          dist[u] = dist[v] + graph[v][u];
        }
      }
    }
  }
  for (int i = 0; i < MAX_STATION_ID; i++) {
    printf("%s to %s: %i\n", STATIONS[origin].name, STATIONS[i].name, dist[i]);
  }
}

int** get_graph_from_connections(const Connection connections[]) {
  int **out = malloc(MAX_STATION_ID * sizeof(int*));
  for (int i = 0; i < MAX_STATION_ID; i++) {
    out[i] = malloc(MAX_STATION_ID * sizeof(int));
  }
  // Initialise graph with every station unconnected
  for (int i = 0; i < MAX_STATION_ID; i++) {
    for (int j = 0; j < MAX_STATION_ID; j++) {
      out[i][j] = -1;
    }
  }
  // Populate graph with connections
  for (int i = 0; i < NUM_CONNECTIONS; i++) {
    out[connections[i].station1 - 1][connections[i].station2 - 1] = connections[i].time;
    out[connections[i].station2 - 1][connections[i].station1 - 1] = connections[i].time;
  }
  return out;
}

int main() {
  int** graph = get_graph_from_connections(CONNECTIONS);

  dijkstra(graph, 0);

  return 0;
}
