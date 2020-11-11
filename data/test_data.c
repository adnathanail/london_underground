//
// Created by Alexander Nathanail on 09/11/2020.
//
// Try to represent the below test adjacency matrix in the format the tube data is in
//{ { -1, 4, -1, -1, -1, -1, -1, 8, -1 },
//{ 4, -1, 8, -1, -1, -1, -1, 11, -1 },
//{ -1, 8, -1, 7, -1, 4, -1, -1, 2 },
//{ -1, -1, 7, -1, 9, 14, -1, -1, -1 },
//{ -1, -1, -1, 9, -1, 10, -1, -1, -1 },
//{ -1, -1, 4, 14, 10, -1, 2, -1, -1 },
//{ -1, -1, -1, -1, -1, 2, -1, 1, 6 },
//{ 8, 11, -1, -1, -1, -1, 1, -1, 7 },
//{ -1, -1, 2, -1, -1, -1, 6, 7, -1 } };

#include "test_data.h"

// The first 9 STATIONS
const Station STATIONS[NUM_STATIONS] = {
  { .id = 1, .latitude = 51.5028, .longitude = -0.2801, .name = "Acton Town", .zone = 3, .total_lines = 2, .rail = 0 },
  { .id = 2, .latitude = 51.5143, .longitude = -0.0755, .name = "Aldgate", .zone = 1, .total_lines = 2, .rail = 0 },
  { .id = 3, .latitude = 51.5154, .longitude = -0.0726, .name = "Aldgate East", .zone = 1, .total_lines = 2, .rail = 0 },
  { .id = 4, .latitude = 51.5107, .longitude = -0.013, .name = "All Saints", .zone = 2, .total_lines = 1, .rail = 0 },
  { .id = 5, .latitude = 51.5407, .longitude = -0.2997, .name = "Alperton", .zone = 4, .total_lines = 1, .rail = 0 },
  { .id = 6, .latitude = 51.5322, .longitude = -0.1058, .name = "Angel", .zone = 1, .total_lines = 1, .rail = 0 },
  { .id = 7, .latitude = 51.5653, .longitude = -0.1353, .name = "Archway", .zone = 2.5, .total_lines = 1, .rail = 0 },
  { .id = 8, .latitude = 51.6164, .longitude = -0.1331, .name = "Arnos Grove", .zone = 4, .total_lines = 1, .rail = 0 },
  { .id = 9, .latitude = 51.5586, .longitude = -0.1059, .name = "Arsenal", .zone = 2, .total_lines = 1, .rail = 0 },
};

const Connection CONNECTIONS[NUM_CONNECTIONS] = {
  { .station1 = 1, .station2 = 2, .line = 1, .time = 4 },
  { .station1 = 1, .station2 = 8, .line = 1, .time = 8 },
  { .station1 = 2, .station2 = 3, .line = 1, .time = 8 },
  { .station1 = 2, .station2 = 8, .line = 1, .time = 11 },
  { .station1 = 3, .station2 = 4, .line = 1, .time = 7 },
  { .station1 = 3, .station2 = 6, .line = 1, .time = 4 },
  { .station1 = 3, .station2 = 9, .line = 1, .time = 2 },
  { .station1 = 4, .station2 = 5, .line = 1, .time = 9 },
  { .station1 = 4, .station2 = 6, .line = 1, .time = 14 },
  { .station1 = 5, .station2 = 6, .line = 1, .time = 10 },
  { .station1 = 6, .station2 = 7, .line = 1, .time = 2 },
  { .station1 = 7, .station2 = 8, .line = 1, .time = 1 },
  { .station1 = 7, .station2 = 9, .line = 1, .time = 6 },
  { .station1 = 8, .station2 = 9, .line = 1, .time = 7 },
};

const Line LINES[NUM_LINES] = {
  { .line = 1, .name = "Bakerloo Line", .colour = "AE6017" },
};