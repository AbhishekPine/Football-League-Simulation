#include <stdio.h>

int main() {
    char* countries[5] = {"spain", "england", "germany", "italy", "france"};
    char* leagues[5] = {
        "La Liga Santander",
        "English Premier League",
        "Bundesliga",
        "Seria A",
        "Ligue 1"
    };
    char* spainTeams[20] = {
        "Real Madrid",
        "FC Barcelona",
        "Valencia CF",
        "Atlético Madrid",
        "RC Celta",
        "Real Betis",
        "Villarreal CF",
        "Real Sociedad",
        "Athletic Club de Bilbao",
        "Deportivo Alavés",
        "Getafe CF",
        "Sevilla FC",
        "Levante UD",
        "Granada CF",
        "CA Osasuna",
        "Real Valladolid CF",
        "RCD Espanyol",
        "SD Eibar",
        "RCD Mallorca",
        "CD Leganés"
    };
    char* englandTeams[20] = {
        "Arsenal",
        "Bournemouth",
        "Brighton & Hove Albion",
        "Burnley",
        "Sheffield United",
        "Chelsea",
        "Crystal Palace",
        "Everton",
        "Norwich City",
        "Aston Villa",
        "Leicester City",
        "Liverpool",
        "Manchester City",
        "Manchester United",
        "Newcastle United",
        "Southampton",
        "Tottenham Hotspur",
        "Watford",
        "West Ham United",
        "Wolverhampton Wanderers"
    };
    char* germanyTeams[18] = {
        "FC Bayern München",
        "Borussia Dortmund",
        "Bayer 04 Leverkusen",
        "RB Leipzig",
        "Eintracht Frankfurt",
        "TSG 1899 Hoffenheim",
        "1. FC Köln",
        "Borussia Mönchengladbach",
        "SV Werder Bremen",
        "Hertha BSC",
        "VfL Wolfsburg",
        "FC Schalke 04",
        "SC Freiburg",
        "FC Augsburg",
        "1. FSV Mainz 05",
        "1. FC Union Berlin",
        "Fortuna Düsseldorf",
        "SC Paderborn 07"
    };
    char* italyTeams[20] = {
        "Juventus",
        "Napoli",
        "Lazio",
        "Milan",
        "Torino",
        "Sampdoria",
        "Inter",
        "Brescia",
        "Cagliari",
        "Sassuolo",
        "Roma",
        "Fiorentina",
        "Genoa",
        "Atalanta",
        "Bologna",
        "SPAL",
        "Udinese",
        "Hellas Verona",
        "Parma",
        "Lecce"
    };
    char* franceTeams[20] = {
        "Paris Saint-Germain",
        "AS Saint-Étienne",
        "Olympique de Marseille",
        "AS Monaco",
        "Olympique Lyonnais",
        "FC Girondins de Bordeaux",
        "LOSC Lille",
        "FC Nantes",
        "RC Strasbourg Alsace",
        "Montpellier HSC",
        "Angers SCO",
        "OGC Nice",
        "Stade Rennais FC",
        "Nîmes Olympique",
        "Toulouse Football Club",
        "FC Metz",
        "Amiens SC",
        "Stade de Reims",
        "Dijon FCO",
        "Stade Brestois 29"
    };

    printf("Countries:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d: %s\n", i+1, countries[i]);
    }

    printf("\nLeagues:\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: %s\n", countries[i], leagues[i]);
    }

    printf("\nTeams:\n");
    printf("Spain:\n");
    for (int i = 0; i < 20; i++) {
        printf("%s\n", spainTeams[i]);
    }

    printf("\nEngland:\n");
    for (int i = 0; i < 20; i++) {
        printf("%s\n", englandTeams[i]);
    }

    printf("\nGermany:\n");
    for (int i = 0; i < 18; i++) {
        printf("%s\n", germanyTeams[i]);
    }

    printf("\nItaly:\n");
    for (int i = 0; i < 20; i++) {
        printf("%s\n", italyTeams[i]);
    }

    printf("\nFrance:\n");
    for (int i = 0; i < 20; i++) {
        printf("%s\n", franceTeams[i]);
    }

    return 0;
}


