//
// Created by Alexander Nathanail on 10/11/2020.
//

#include <strings.h>
#include <ctype.h>

#include "utils.h"

void str_tolower(char* s) {
  for (int i = 0; i < strlen(s); i++) {
    s[i] = (char) tolower(s[i]);
  }
}