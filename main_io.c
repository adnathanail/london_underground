#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

const int MAX_COL_WIDTH = 1000;
const int MAX_NUM_COLS = 1000;
const int MAX_TABLE_HEIGHT = 1000;

void clear_string(char s[]) {
  for (int i = 0; i < MAX_COL_WIDTH; i++) {
    s[i] = '\0';
  }
}

void arrstrcpy(char dst[][MAX_COL_WIDTH], const char src[][MAX_COL_WIDTH], int num_items) {
  for (int i = 0; i < num_items; i++) {
    strcpy(dst[i], src[i]);
  }
}

//char** read_csv(FILE *fp, int num_columns) {
//  char** out = malloc(1 * sizeof(char*));
//
//  int row_count = 0;
//  int col_count = 0;
//  char ch;
//  char rows[MAX_TABLE_HEIGHT][num_columns][MAX_COL_WIDTH];
//  char row[num_columns][MAX_COL_WIDTH];
//  char column[MAX_COL_WIDTH] = "";
//  while ((ch = (char)fgetc(fp)) != EOF) {
//////    printf("%c", ch);
//    if (ch == '\n') {
//      if (row_count > 0) {
//        arrstrcpy(rows[row_count], row, col_count);
//      }
//      row_count += 1;
//      col_count = 0;
//    } else if (row_count > 0) {  // Ignore the first row
//      if (ch == ',') {
//        strcpy(row[col_count], column);
//        clear_string(column);
//        col_count += 1;
//      } else {
//        strncat(column, &ch, 1);
//      }
//    }
//  }
//  for (int i = 0; i < num_columns; i++) {
//    printf("%s\t", row[i]);
//  }
//  return out;
//}

char** read_csv(FILE *fp, int num_columns) {
  char** out = malloc(1 * sizeof(char*));

  int row_count = 0;
  int col_count = 0;
  char ch;
  char*** rows = calloc(sizeof(char**), MAX_TABLE_HEIGHT);
  char** row = calloc(sizeof(char*), MAX_NUM_COLS);
  char* column = calloc(sizeof(char), MAX_COL_WIDTH);
  while ((ch = (char)fgetc(fp)) != EOF) {
////    printf("%c", ch);
    if (ch == '\n') {
      if (row_count > 0) {
        memcpy(rows[row_count], row, sizeof(char*) * MAX_NUM_COLS);
        for (int i = 0; i < MAX_NUM_COLS; i++) {
          row[i] = 0;
        }
      }
      row_count += 1;
      col_count = 0;
    } else if (row_count > 0) {  // Ignore the first row
      if (ch == ',') {
        strcpy(row[col_count], column);
        clear_string(column);
        col_count += 1;
      } else {
        strncat(column, &ch, 1);
      }
    }
  }
  for (int i = 0; i < num_columns; i++) {
    printf("%s\t", row[i]);
  }
  return out;
}

int main() {
  FILE *stations_fp;
//  int id;
//  float latitude;
//  float longitude;
//  char name[MAX_COL_WIDTH];
//  char display_name[MAX_COL_WIDTH];
//  int zone;
//  int total_lines;
//  int rail;

  stations_fp = fopen("/Users/adnathanail/Documents/Projects/london-underground/data/london.stations.csv", "r");
  read_csv(stations_fp, 8);
//  char ch;
//  while((ch = (char)fgetc(stations_fp)) != '\n') {
//    printf("%c", ch);
//  }
////  fscanf(stations_fp, "%i,%f,%f,\"%[^\"]+\",\"%[^\"]+\"", &id, &latitude, &longitude, name, display_name);
////  fscanf(stations_fp, "%i,%f,%f,\"%[^\"]+\",\"%[^\"]+\",\"%i\",%i,%i", &id, &latitude, &longitude, name, display_name, &zone, &total_lines, &rail);
////  printf("%i %f %f %s %s %s %i %i", id, latitude, longitude, name, display_name, zone, total_lines, rail);
//  printf("%i %f %f %s %s", id, latitude, longitude, name, display_name);

  fclose(stations_fp);

  return 0;
}
