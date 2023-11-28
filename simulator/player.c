#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ATTACKER "attacker"
#define MIDFIELDER "midfielder"
#define DEFENDER "defender"
#define GOALKEEPER "goalkeeper"

#define STARTER "starter"
#define SUBSTITUTE "substitute"
#define RESERVE "reserve"

#define NUM_GOALKEEPER_ATTRIBUTES 6

typedef struct {
    char* name;
    char* nationality;
    int overall;
    int pace;
    int shooting;
    int passing;
    int dribbling;
    int defending;
    int physic;
    int keeping;
    char* team_status;
    char* position;
} Player;

char* GOALKEEPER_ATTRIBUTES[NUM_GOALKEEPER_ATTRIBUTES] = {
    "gk_diving",
    "gk_handling",
    "gk_kicking",
    "gk_reflexes",
    "gk_speed",
    "gk_positioning"
};

void set_player_position(Player* player, char* player_positions);
void set_goalkeeper_rating(Player* player, int* stats);
int is_attacker(Player* player);
int is_midfielder(Player* player);
int is_defender(Player* player);
int is_goalkeeper(Player* player);
void set_as_starter(Player* player);
int is_starter(Player* player);

int main() {
    // Example usage
    Player* player = (Player*)malloc(sizeof(Player));
    player->name = "John Doe";
    player->nationality = "England";
    player->overall = 80;
    player->pace = 85;
    player->shooting = 75;
    player->passing = 80;
    player->dribbling = 85;
    player->defending = 70;
    player->physic = 75;
    player->keeping = 0;
    player->team_status = RESERVE;
    player->position = "ST, CF";
    
    set_player_position(player, player->position);
    set_goalkeeper_rating(player, NULL);
    
    printf("Player name: %s\n", player->name);
    printf("Player nationality: %s\n", player->nationality);
    printf("Player overall: %d\n", player->overall);
    printf("Player pace: %d\n", player->pace);
    printf("Player shooting: %d\n", player->shooting);
    printf("Player passing: %d\n", player->passing);
    printf("Player dribbling: %d\n", player->dribbling);
    printf("Player defending: %d\n", player->defending);
    printf("Player physic: %d\n", player->physic);
    printf("Player keeping: %d\n", player->keeping);
    printf("Player team status: %s\n", player->team_status);
    printf("Player position: %s\n", player->position);
    
    free(player);
    
    return 0;
}

void set_player_position(Player* player, char* player_positions) {
    char* main_position = strtok(player_positions, ",");
    
    if (strstr(main_position, "B") != NULL) {
        player->position = DEFENDER;
    } else if (strstr(main_position, "M") != NULL) {
        player->position = MIDFIELDER;
    } else if (strstr(main_position, "S") != NULL || strstr(main_position, "F") != NULL || strstr(main_position, "W") != NULL) {
        player->position = ATTACKER;
    } else {
        player->position = GOALKEEPER;
    }
}

void set_goalkeeper_rating(Player* player, int* stats) {
    if (is_goalkeeper(player)) {
        int gk_rating = 0;
        for (int i = 0; i < NUM_GOALKEEPER_ATTRIBUTES; i++) {
            gk_rating += stats[i];
        }
        player->keeping = gk_rating / NUM_GOALKEEPER_ATTRIBUTES;
    }
}

int is_attacker(Player* player) {
    return strcmp(player->position, ATTACKER) == 0;
}

int is_midfielder(Player* player) {
    return strcmp(player->position, MIDFIELDER) == 0;
}

int is_defender(Player* player) {
    return strcmp(player->position, DEFENDER) == 0;
}

int is_goalkeeper(Player* player) {
    return strcmp(player->position, GOALKEEPER) == 0;
}

void set_as_starter(Player* player) {
    player->position = STARTER;
}

int is_starter(Player* player) {
    return strcmp(player->position, STARTER) == 0;
}


