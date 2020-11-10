//
// Created by Alexander Nathanail on 10/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include <errno.h>
#include "data_types.h"

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
  int out = -1;

  while (out == -1) {
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

int get_station(char* designation) {  // Designation is things like origin/destination
  char* prompt = calloc(6 + strlen(designation) + 6 + 13 + 1, sizeof(char));
  strcpy(prompt, "Enter ");
  strcat(prompt, designation);
  strcat(prompt, " station ID: ");
  int station = read_int(prompt);

  free(prompt);
  return station;
}