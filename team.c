#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player {
    char long_name[100];
    int overall;
    int is_attacker;
    int is_defender;
    int is_midfielder;
    int is_goalkeeper;
};

struct Manager {
    int formation[3];
};

struct Team {
    char name[100];
    struct Manager manager;
    struct Player players[100];
    struct Player squad_attackers[100];
    struct Player squad_midfielders[100];
    struct Player squad_defenders[100];
    struct Player squad_goalkeeper[1];
    int num_attackers;
    int num_midfielders;
    int num_defenders;
    int attack;
    int midfield;
    int defence;
};

void set_players(struct Team *team);
void set_stats(struct Team *team);
void set_squad(struct Team *team);

int main() {
    struct Team team;
    strcpy(team.name, "team_name");
    set_players(&team);
    set_stats(&team);
    set_squad(&team);
    return 0;
}

void set_players(struct Team *team) {
    // Read player data from file and populate team players
}

void set_stats(struct Team *team) {
    int i;
    int num_attackers = 0;
    int num_midfielders = 0;
    int num_defenders = 0;
    int sum_attackers = 0;
    int sum_defenders = 0;
    int sum_goalkeepers = 0;
    int sum_midfielders = 0;
    for (i = 0; i < 100; i++) {
        if (team->players[i].is_attacker) {
            num_attackers++;
            sum_attackers += team->players[i].overall;
        }
        if (team->players[i].is_defender) {
            num_defenders++;
            sum_defenders += team->players[i].overall;
        }
        if (team->players[i].is_goalkeeper) {
            num_defenders++;
            sum_goalkeepers += team->players[i].overall;
        }
        if (team->players[i].is_midfielder) {
            num_midfielders++;
            sum_midfielders += team->players[i].overall;
        }
    }
    team->attack = sum_attackers / num_attackers;
    team->defence = (sum_defenders + sum_goalkeepers) / (num_defenders + num_goalkeepers);
    team->midfield = sum_midfielders / num_midfielders;
}

void set_squad(struct Team *team) {
    int i;
    int j;
    int k;
    int l;
    int m;
    int n;
    int num_attackers = team->manager.formation[0];
    int num_midfielders = team->manager.formation[1];
    int num_defenders = team->manager.formation[2];
    struct Player temp;
    for (i = 0; i < 100; i++) {
        for (j = i + 1; j < 100; j++) {
            if (team->players[i].overall < team->players[j].overall) {
                temp = team->players[i];
                team->players[i] = team->players[j];
                team->players[j] = temp;
            }
        }
    }
    for (k = 0; k < num_attackers; k++) {
        team->squad_attackers[k] = team->players[k];
        team->squad_attackers[k].is_starter = 1;
    }
    for (l = 0; l < num_midfielders; l++) {
        team->squad_midfielders[l] = team->players[l];
        team->squad_midfielders[l].is_starter = 1;
    }
    for (m = 0; m < num_defenders; m++) {
        team->squad_defenders[m] = team->players[m];
        team->squad_defenders[m].is_starter = 1;
    }
    team->squad_goalkeeper[0] = team->players[0];
    team->squad_goalkeeper[0].is_starter = 1;
}


