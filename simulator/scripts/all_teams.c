#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char club[50];
} DataFrame;

typedef struct {
    DataFrame* data;
    int size;
} DataFrameArray;

DataFrameArray read_pickle(const char* filename) {
    // Read pickle file and return DataFrameArray
    // Implementation not provided
}

void print_unique_clubs(DataFrameArray df) {
    char unique_clubs[100][50];
    int num_unique_clubs = 0;

    for (int i = 0; i < df.size; i++) {
        int is_unique = 1;
        for (int j = 0; j < num_unique_clubs; j++) {
            if (strcmp(df.data[i].club, unique_clubs[j]) == 0) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            strcpy(unique_clubs[num_unique_clubs], df.data[i].club);
            num_unique_clubs++;
        }
    }

    for (int i = 0; i < num_unique_clubs; i++) {
        printf("%s\n", unique_clubs[i]);
    }
}

int main() {
    DataFrameArray df_player_data = read_pickle("simulator/resources/player_data");
    print_unique_clubs(df_player_data);

    return 0;
}


