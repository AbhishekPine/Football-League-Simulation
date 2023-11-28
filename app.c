#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int league_no;
} League;

void simulate_league(League* league) {
    // simulate league logic
}

int get_league_input() {
    int num;
    printf("Enter the league number: ");
    scanf("%d", &num);
    if (num < 1 || num > 5) {
        printf("Please enter a valid input!\n");
        return get_league_input();
    }
    return num;
}

int main() {
    char welcome_message[] = "Welcome to the league simulator!";
    char leagues_message[] = "Enter the league number (1-5): ";
    
    printf("%s\n", welcome_message);
    int league_no = get_league_input();
    League league;
    league.league_no = league_no;
    simulate_league(&league);
    
    return 0;
}

