//
// Created by Alexander Nathanail on 10/11/2020.
//

#ifndef LONDON_UNDERGROUND_DATA_H
#define LONDON_UNDERGROUND_DATA_H

#include "../libs/data_types.h"

#define MAX_STATION_ID 303
#define NUM_STATIONS 302
// ^ not NUM_STATIONS as there are missing station ID's
//   this will lead to some unused rows/columns in the adjacency matrix but it is negligible
#define MAX_NAME_LENGTH 100
extern const Station STATIONS[];
#define NUM_CONNECTIONS 406
extern const Connection CONNECTIONS[];
#define NUM_LINES 13
extern const Line LINES[];

#endif //LONDON_UNDERGROUND_DATA_H
