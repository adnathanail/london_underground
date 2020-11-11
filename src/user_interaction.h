//
// Created by Alexander Nathanail on 10/11/2020.
//

#ifndef LONDON_UNDERGROUND_USER_INTERACTION_H
#define LONDON_UNDERGROUND_USER_INTERACTION_H

#include "data_types.h"

char* read_string(char* prompt);
int read_int(char* prompt);
int get_station_id(char* designation, PartialStation** stations_map, int station_arr_length);
void station_search(PartialStation** stations_map, int station_arr_length);

#endif //LONDON_UNDERGROUND_USER_INTERACTION_H
