#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* Club;
    int Matches_Played;
    int Wins;
    int Draws;
    int Losses;
    int Points;
    int GF;
    int GA;
    int GD;
} LeagueTable;

typedef struct {
    char* name;
    int players;
} Team;

typedef struct {
    Team** teams;
    int team_count;
} League;

LeagueTable* init_league_table(char** team_names, int team_count) {
    LeagueTable* table = malloc(team_count * sizeof(LeagueTable));
    for (int i = 0; i < team_count; i++) {
        table[i].Club = strdup(team_names[i]);
        table[i].Matches_Played = 0;
        table[i].Wins = 0;
        table[i].Draws = 0;
        table[i].Losses = 0;
        table[i].Points = 0;
        table[i].GF = 0;
        table[i].GA = 0;
        table[i].GD = 0;
    }
    return table;
}

void show_league_table(LeagueTable* table, int team_count) {
    printf("| Club | Matches Played | Wins | Draws | Losses | Points | GF | GA | GD |\n");
    printf("|------|----------------|------|-------|--------|--------|----|----|----|\n");
    for (int i = 0; i < team_count; i++) {
        printf("| %s | %d | %d | %d | %d | %d | %d | %d | %d |\n", table[i].Club, table[i].Matches_Played, table[i].Wins, table[i].Draws, table[i].Losses, table[i].Points, table[i].GF, table[i].GA, table[i].GD);
    }
}

void update_league_table(LeagueTable* table, int team_count, char* winner, char* loser, int num_winner_goals, int num_loser_goals) {
    int goal_difference = num_winner_goals - num_loser_goals;
    for (int i = 0; i < team_count; i++) {
        if (strcmp(table[i].Club, winner) == 0) {
            table[i].Matches_Played += 1;
            table[i].Wins += 1;
            table[i].Points += 3;
            table[i].GF += num_winner_goals;
            table[i].GA += num_loser_goals;
            table[i].GD += goal_difference;
        } else if (strcmp(table[i].Club, loser) == 0) {
            table[i].Matches_Played += 1;
            table[i].Losses += 1;
            table[i].GA += num_winner_goals;
            table[i].GF += num_loser_goals;
            table[i].GD -= goal_difference;
        } else {
            table[i].Matches_Played += 1;
            table[i].Draws += 1;
            table[i].Points += 1;
            table[i].GF += num_winner_goals;
            table[i].GA += num_loser_goals;
        }
    }
    for (int i = 0; i < team_count - 1; i++) {
        for (int j = 0; j < team_count - i - 1; j++) {
            if (table[j].Points < table[j + 1].Points) {
                LeagueTable temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            }
        }
    }
}

void simulate_match(LeagueTable* table, int team_count, Team** teams, char* home_team_name, char* away_team_name) {
    Team* home_team;
    Team* away_team;
    for (int i = 0; i < team_count; i++) {
        if (strcmp(teams[i]->name, home_team_name) == 0) {
            home_team = teams[i];
        } else if (strcmp(teams[i]->name, away_team_name) == 0) {
            away_team = teams[i];
        }
    }
    printf("Simulating match between %s and %s\n", home_team->name, away_team->name);
    int num_winner_goals = 0;
    int num_loser_goals = 0;
    update_league_table(table, team_count, home_team->name, away_team->name, num_winner_goals, num_loser_goals);
}

void simulate_week(LeagueTable* table, int team_count, Team** teams, char*** schedule, int week) {
    char** week_schedule = schedule[week];
    for (int i = 0; i < team_count / 2; i++) {
        char* home_team_name = week_schedule[i * 2];
        char* away_team_name = week_schedule[i * 2 + 1];
        simulate_match(table, team_count, teams, home_team_name, away_team_name);
    }
}

void simulate_league(LeagueTable* table, int team_count, Team** teams, char*** schedule, int schedule_length) {
    for (int week = 0; week < schedule_length; week++) {
        simulate_week(table, team_count, teams, schedule, week);
        show_league_table(table, team_count);
    }
}

int main() {
    char* team_names[] = {"Team 1", "Team 2", "Team 3", "Team 4"};
    int team_count = sizeof(team_names) / sizeof(team_names[0]);
    Team** teams = malloc(team_count * sizeof(Team*));
    for (int i = 0; i < team_count; i++) {
        teams[i] = malloc(sizeof(Team));
        teams[i]->name = strdup(team_names[i]);
        teams[i]->players = 0;
    }
    char** schedule[] = {
        {"Team 1", "Team 2", "Team 3", "Team 4"},
        {"Team 1", "Team 3", "Team 2", "Team 4"},
        {"Team 1", "Team 4", "Team 2", "Team 3"}
    };
    int schedule_length = sizeof(schedule) / sizeof(schedule[0]);
    LeagueTable* table = init_league_table(team_names, team_count);
    simulate_league(table, team_count, teams, schedule, schedule_length);
    return 0;
}


