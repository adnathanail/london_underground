//
// Created by Alexander Nathanail on 10/11/2020.
//

#ifndef LONDON_UNDERGROUND_DATA_H
#define LONDON_UNDERGROUND_DATA_H

#endif //LONDON_UNDERGROUND_DATA_H

#include "types.c"

#define MAX_STATION_ID 303
// ^ not NUM_STATIONS as there are missing station ID's
//   this will lead to some unused rows/columns in the adjacency matrix but it is negligible
extern const Station STATIONS[];
#define NUM_CONNECTIONS 406
extern const Connection CONNECTIONS[];
#define NUM_LINES 13
extern const Line LINES[];