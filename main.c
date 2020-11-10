#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "data/test_data.h"

int get_next_closest_node(int dist[NUM_STATIONS], int Q[NUM_STATIONS]) {
  int closest_node = -1;
  int closes_node_distance = INT_MAX;
  int i = 0;
  while (Q[i] != -1 && i < NUM_STATIONS) {
    if (dist[Q[i]] < closes_node_distance || closest_node == -1) {
      closest_node = Q[i];
      closes_node_distance = dist[Q[i]];
    }
    i++;
  }
  return closest_node;
}

void pop(int queue[], int val) {
  int shifting = 0;
  for (int i = 0; i < NUM_STATIONS; i++) {
    if (queue[i] == val) {
      shifting = 1;
    }
    if (shifting) {
      queue[i] = queue[i + 1];
    }
  }
  queue[NUM_STATIONS - 1] = -1;
}

void add(int set[], int val) {
  for (int i = 0; i < NUM_STATIONS; i++) {
    if (set[i] == -1) {
      set[i] = val;
      break;
    }
  }
}

void dijkstra(int** graph, int s) {
  // Dijkstra implementation based off https://brilliant.org/wiki/dijkstras-short-path-finder/
  int dist[NUM_STATIONS];
  for (int i = 0; i < NUM_STATIONS; i++) {
    dist[i] = INT_MAX;
  }
  dist[s] = 0;
  int Q[NUM_STATIONS];
  for (int i = 0; i < NUM_STATIONS; i++) {
    Q[i] = i;
  }
  int S[NUM_STATIONS] = {-1};
  for (int i = 0; i < NUM_STATIONS; i++) {
    S[i] = -1;
  }
  while (Q[0] != -1) {
    int v = get_next_closest_node(dist, Q);
    pop(Q, v);
    add(S, v);
    for (int u = 0; u < NUM_STATIONS; u++) {
      if (graph[v][u] != -1) {
        if ((dist[v] + graph[v][u]) < dist[u]) {
          dist[u] = dist[v] + graph[v][u];
        }
      }
    }
  }
  for (int i = 0; i < NUM_STATIONS; i++) {
    printf("%i to %i: %i\n", s, i, dist[i]);
  }
}

int** get_graph_from_connections(const Connection connections[]) {
  int **out = malloc(NUM_STATIONS * sizeof(int*));
  for (int i = 0; i < NUM_STATIONS; i++) {
    out[i] = malloc(NUM_STATIONS * sizeof(int));
  }
  // Initialise graph with every station unconnected
  for (int i = 0; i < NUM_STATIONS; i++) {
    for (int j = 0; j < NUM_STATIONS; j++) {
      out[i][j] = -1;
    }
  }
  // Populate graph with connections
  for (int i = 0; i < NUM_CONNECTIONS; i++) {
    out[connections[i].station1][connections[i].station2] = connections[i].time;
    out[connections[i].station2][connections[i].station1] = connections[i].time;
  }
  return out;
}

int main() {
  int** graph = get_graph_from_connections(CONNECTIONS);

  dijkstra(graph, 0);

  return 0;
}
