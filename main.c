#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>

#define NUM_NODES 10

int get_next_closest_node(int dist[NUM_NODES], int Q[NUM_NODES]) {
  int closest_node = -1;
  int closes_node_distance = INT_MAX;
  int i = 0;
  while (Q[i] != -1 && i < NUM_NODES) {
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
  for (int i = 0; i < NUM_NODES; i++) {
    if (queue[i] == val) {
      shifting = 1;
    }
    if (shifting) {
      queue[i] = queue[i + 1];
    }
  }
  queue[NUM_NODES - 1] = -1;
}

void add(int set[], int val) {
  for (int i = 0; i < NUM_NODES; i++) {
    if (set[i] == -1) {
      set[i] = val;
      break;
    }
  }
}

void dijkstra(int graph[NUM_NODES][NUM_NODES], int s) {
  // Dijkstra implementation based off https://brilliant.org/wiki/dijkstras-short-path-finder/
  int dist[NUM_NODES];
  for (int i = 0; i < NUM_NODES; i++) {
    dist[i] = INT_MAX;
  }
  dist[s] = 0;
  int Q[NUM_NODES];
  for (int i = 0; i < NUM_NODES; i++) {
    Q[i] = i;
  }
  int S[NUM_NODES] = {-1};
  for (int i = 0; i < NUM_NODES; i++) {
    S[i] = -1;
  }
  while (Q[0] != -1) {
    int v = get_next_closest_node(dist, Q);
    pop(Q, v);
    add(S, v);
    for (int u = 0; u < NUM_NODES - 1; u++) {
      if (graph[v][u] != -1) {
        if ((dist[v] + graph[v][u]) < dist[u]) {
          dist[u] = dist[v] + graph[v][u];
        }
      }
    }
  }
  for (int i = 0; i < NUM_NODES - 1; i++) {
    printf("%i to %i: %i\n", s, i, dist[i]);
  }
}

int main() {
  int graph[NUM_NODES][NUM_NODES] = { { -1, 4, -1, -1, -1, -1, -1, 8, -1 },
                      { 4, -1, 8, -1, -1, -1, -1, 11, -1 },
                      { -1, 8, -1, 7, -1, 4, -1, -1, 2 },
                      { -1, -1, 7, -1, 9, 14, -1, -1, -1 },
                      { -1, -1, -1, 9, -1, 10, -1, -1, -1 },
                      { -1, -1, 4, 14, 10, -1, 2, -1, -1 },
                      { -1, -1, -1, -1, -1, 2, -1, 1, 6 },
                      { 8, 11, -1, -1, -1, -1, 1, -1, 7 },
                      { -1, -1, 2, -1, -1, -1, 6, 7, -1 } };

  dijkstra(graph, 0);

  return 0;
}
