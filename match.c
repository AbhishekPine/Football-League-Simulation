#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Event {
    char* event;
    char* side;
    int minute;
};

struct Side {
    char* name;
    int defence;
    int midfield;
    int attack;
    struct Player* players;
    struct Player* squad;
};

struct Player {
    char* name;
    int age;
    int rating;
};

struct Match {
    struct Side home_side;
    struct Side away_side;
    struct Event* matchevents;
    int home_goals;
    int away_goals;
};

struct Odds {
    double Event;
    struct TeamOdds Home;
    struct TeamOdds Away;
};

struct TeamOdds {
    double Probability;
    struct EventOdds Events;
};

struct EventOdds {
    double Attempt;
    double Free_kick_won;
    double Yellow_card;
    double Second_yellow_card;
    double Red_card;
    double On_target;
    double Saved;
    double Off_target;
    double Blocked;
    double Hit_the_bar;
    double Goal;
};

struct Match reverse;
char* eventkeys;
char* foulkeys;

void set_odds(struct Match* match);
void add_event(struct Match* match, struct Event* event);
void set_events(struct Match* match);
void track_event(struct Match* match, struct Event* event);
void evaluate_match_result(struct Match* match);
void show_match_result(struct Match* match);

int main() {
    srand(time(NULL));
    
    struct Match match;
    struct Side home_side;
    struct Side away_side;
    
    match.home_side = home_side;
    match.away_side = away_side;
    
    set_odds(&match);
    set_events(&match);
    evaluate_match_result(&match);
    show_match_result(&match);
    
    return 0;
}

void set_odds(struct Match* match) {
    double hdf = (match->home_side.defence * match->home_side.defence * match->home_side.midfield) / (match->away_side.attack * match->away_side.attack * match->away_side.midfield);
    double adf = (match->away_side.defence * match->away_side.defence * match->away_side.midfield) / (match->home_side.attack * match->home_side.attack * match->home_side.midfield);
    
    for (int minute = 0; minute < 100; minute++) {
        match->odds[minute].Home.Events.Attempt = match->odds[minute].Home.Events.Attempt / (adf * adf * adf);
        match->odds[minute].Away.Events.Attempt = match->odds[minute].Away.Events.Attempt / (hdf * hdf * hdf);
    }
}

void add_event(struct Match* match, struct Event* event) {
    struct Event* e = event->evaluate_event();
    
    if (strcmp(e->event, "Substitution") == 0) {
        if (match->stats[e->side].Substitution < 3) {
            track_event(match, e);
        }
    } else {
        track_event(match, e);
    }
    
    e->show_event();
    match->matchevents = realloc(match->matchevents, (sizeof(struct Event) * (sizeof(match->matchevents) / sizeof(struct Event) + 1)));
    match->matchevents[sizeof(match->matchevents) / sizeof(struct Event)] = *e;
}

void set_events(struct Match* match) {
    for (int minute = 0; minute < 100; minute++) {
        for (int i = 0; i < 135; i++) {
            if ((double)rand() / RAND_MAX < match->odds[minute].Event) {
                double plist[2];
                plist[0] = match->odds[minute].Home.Probability;
                plist[1] = match->odds[minute].Away.Probability;
                struct Side* side = (double)rand() / RAND_MAX < plist[0] ? &match->home_side : &match->away_side;
                char* event = NULL;
                double event_odds[11];
                event_odds[0] = match->odds[minute].Home.Events.Attempt;
                event_odds[1] = match->odds[minute].Home.Events.Free_kick_won;
                event_odds[2] = match->odds[minute].Home.Events.Yellow_card;
                event_odds[3] = match->odds[minute].Home.Events.Second_yellow_card;
                event_odds[4] = match->odds[minute].Home.Events.Red_card;
                event_odds[5] = match->odds[minute].Home.Events.On_target;
                event_odds[6] = match->odds[minute].Home.Events.Saved;
                event_odds[7] = match->odds[minute].Home.Events.Off_target;
                event_odds[8] = match->odds[minute].Home.Events.Blocked;
                event_odds[9] = match->odds[minute].Home.Events.Hit_the_bar;
                event_odds[10] = match->odds[minute].Home.Events.Goal;
                
                double total_odds = 0;
                for (int j = 0; j < 11; j++) {
                    total_odds += event_odds[j];
                }
                
                double random_odds = (double)rand() / RAND_MAX * total_odds;
                double cumulative_odds = 0;
                for (int j = 0; j < 11; j++) {
                    cumulative_odds += event_odds[j];
                    if (random_odds <= cumulative_odds) {
                        event = eventkeys[j];
                        break;
                    }
                }
                
                if (event != NULL) {
                    if (strcmp(event, "Attempt") != 0 && strcmp(event, "Free kick won") != 0 && strcmp(event, "Yellow card") != 0 && strcmp(event, "Second yellow card") != 0 && strcmp(event, "Red card") != 0) {
                        struct Event e;
                        e.event = event;
                        e.side = side->name;
                        e.minute = minute;
                        e.home_side = &match->home_side;
                        e.away_side = &match->away_side;
                        add_event(match, &e);
                    }
                }
            }
        }
    }
}

void track_event(struct Match* match, struct Event* event) {
    if (strcmp(event->side, match->home_side.name) == 0) {
        match->home_stats[event->event] = match->home_stats[event->event] + 1;
    } else {
        match->away_stats[event->event] = match->away_stats[event->event] + 1;
    }
    
    match->stats[match->home_side.name] = match->home_stats;
    match->stats[match->away_side.name] = match->away_stats;
}

void evaluate_match_result(struct Match* match) {
    int hg = match->stats[match->home_side.name].Goal;
    int ag = match->stats[match->away_side.name].Goal;
    
    if (hg == ag) {
        printf("Draw: %s vs %s\n", match->home_side.name, match->away_side.name);
    } else if (hg > ag) {
        printf("Win: %s vs %s\n", match->home_side.name, match->away_side.name);
    } else {
        printf("Win: %s vs %s\n", match->away_side.name, match->home_side.name);
    }
}

void show_match_result(struct Match* match) {
    match->home_goals = match->stats[match->home_side.name].Goal;
    match->away_goals = match->stats[match->away_side.name].Goal;
    
    if (match->home_goals > match->away_goals) {
        printf("%s won the match\n", match->home_side.name);
        printf("Score %d - %d\n", match->home_goals, match->away_goals);
    } else if (match->away_goals > match->home_goals) {
        printf("%s won the match\n", match->away_side.name);
        printf("Score %d - %d\n", match->home_goals, match->away_goals);
    } else {
        printf("The match between %s and %s was a Draw\n", match->home_side.name, match->away_side.name);
        printf("Score %d - %d\n", match->home_goals, match->away_goals);
    }
}


