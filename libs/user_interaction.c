//
// Created by Alexander Nathanail on 10/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "data_types.h"

char* read_string(char* prompt) {
  char buffer[MAX_NAME_LENGTH];
  printf("%s", prompt);
  fgets(buffer, MAX_NAME_LENGTH, stdin);

  size_t inputLength = strlen(buffer);
  char *input = calloc(sizeof(char), inputLength);
  strncpy(input, buffer, inputLength-1);
  input[inputLength-1] = '\0';

  return input;
}

int read_int(char* prompt) {
  char* input = read_string("Enter origin station ID: ");
  int out;
  sscanf(input, "%i", &out);
  free(input);
  return out;
}