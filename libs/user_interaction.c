//
// Created by Alexander Nathanail on 10/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

#include "user_interaction.h"
#include "data_types.h"
#include "xterm_codes.h"
#include "utils.h"

char* read_string(char* prompt) {
  char buffer[MAX_NAME_LENGTH];
  printf("%s", prompt);
  fgets(buffer, MAX_NAME_LENGTH, stdin);

  size_t inputLength = strlen(buffer);
  char *input = calloc(inputLength, sizeof(char));
  strncpy(input, buffer, inputLength-1);
  input[inputLength-1] = '\0';

  return input;
}

int read_int(char* prompt) {
  int out = INT_MIN;

  while (out == INT_MIN) {
    char* input = read_string(prompt);
    char *ptr;

    long tem = strtol(input, &ptr, 10);
    free(input);

    if (tem == LONG_MAX || tem == LONG_MIN) {
      printf("\tError: %s (code %i)\n", strerror(errno), errno);
    } else if (tem) {
      // Working in longs up to this point so that errors from strtol can be detected properly
      out = (int) tem;
    } else {
      printf("\tError: %s is not a number\n", ptr);
    }
  }
  return out;
}

int get_station_id(char* designation, PartialStation** stations_map, int station_arr_length) {  // Designation is things like origin/destination
  printf("%s%s%s\n", XT_UNDL XT_BOLD, designation, XT_RSET);
  int station = -1;
  while (station == -1) {
    int input = read_int("Enter station ID or -1 to search stations: ");
    if (input == -1) {
      station_search(stations_map, station_arr_length);
      continue;
    } else if (input < 0 || input > (station_arr_length - 1) || strlen(stations_map[input]->name) == 0) {
      printf("\tError: '%i' is not a valid station ID\n", input);
      continue;
    }
    station = input;
  }
  printf("\tSelected: %s (ID %i)\n\n", stations_map[station]->name, station);
  return station;
}

void station_search(PartialStation** stations_map, int station_arr_length) {
  char* input;
  char* input_lower = NULL;
  while (1) {
    input = read_string("\tEnter a search term (station name) or -1 to return to station selection: ");
    if (strcmp(input, "-1") == 0) {
      break;
    }
    if (strcmp(input, "") == 0) {
      continue;
    }
    printf("\tStations matching '%s':\n", input);
    input_lower = calloc(strlen(input) + 1, sizeof(char));
    strcpy(input_lower, input);
    str_tolower(input_lower);
    for (int i = 0; i < station_arr_length; i++) {
      if(strstr(stations_map[i]->name_lower, input_lower) != NULL) {
        printf("\t\tID %i\t%s\n", i, stations_map[i]->name);
      }
    }
    free(input);
    free(input_lower);
  }
}