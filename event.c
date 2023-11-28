#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char* event;
    char* side;
    int minute;
    char* player;
} Event;

void set_home_and_away_sides(Event* event, char* home_side, char* away_side) {
    char* sides[2] = {home_side, away_side};
    char* reverse[2] = {away_side, home_side};
    event->sides = sides;
    event->reverse = reverse;
}

void set_player_for_events(Event* eventslist) {
    char* position[4] = {"goalkeeper", "defenders", "midfielders", "attackers"};
    char* players = eventslist[0].side.squad[position];
    char* player = players[rand() % sizeof(players)];
    for (int i = 0; i < sizeof(eventslist); i++) {
        eventslist[i].player = player;
        if (eventslist[i].event == "Saved") {
            eventslist[i].player = eventslist[i].side.squad["goalkeeper"][0];
        }
    }
}

Event* evaluate_event(Event* event) {
    if (event->event == "Attempt") {
        Event* l = malloc(3 * sizeof(Event));
        l[0] = *event;
        char* attodds[3];
        attodds[0] = shot_outcome["Probability"];
        attodds[1] = shot_outcome["Probability"];
        attodds[2] = shot_outcome["Probability"];
        char* att = attodds[rand() % sizeof(attodds)];
        event->event = att;
        l[1] = *event;
        if (event->event == "On target") {
            char* goalodds[2];
            goalodds[0] = shot_outcome["On target"]["is_goal"][0];
            goalodds[1] = shot_outcome["On target"]["is_goal"][1];
            char* goal = goalodds[rand() % sizeof(goalodds)];
            if (goal == "Saved") {
                event->side = event->reverse[event->side];
            }
            event->event = goal;
            l[2] = *event;
        }
        set_player_for_events(l);
        return l;
    } else if (event->event == "Foul") {
        Event* flist = malloc(3 * sizeof(Event));
        flist[0] = *event;
        flist[1] = *event;
        char* cardodds[3];
        cardodds[0] = odds[event->minute][event->sides[event->side]]["Events"]["Yellow card"] / odds[event->minute][event->sides[event->side]]["Events"]["Foul"];
        cardodds[1] = odds[event->minute][event->sides[event->side]]["Events"]["Red card"] / odds[event->minute][event->sides[event->side]]["Events"]["Foul"];
        cardodds[2] = 1 - (cardodds[0] + cardodds[1]);
        char* card = cardodds[rand() % sizeof(cardodds)];
        if (card != "No card") {
            flist[2] = *event;
        }
        set_player_for_events(flist);
        return flist;
    } else {
        Event* l = malloc(sizeof(Event));
        l[0] = *event;
        set_player_for_events(l);
        return l;
    }
}

void show_event(Event* event) {
    printf("%d' %s %s %s\n", event->minute, event->side, event->event, event->player);
}

int main() {
    srand(time(NULL));
    Event event;
    event.event = "Attempt";
    event.side = "Home";
    event.minute = 10;
    event.player = NULL;
    set_home_and_away_sides(&event, "Home", "Away");
    Event* events = evaluate_event(&event);
    for (int i = 0; i < sizeof(events); i++) {
        show_event(&events[i]);
    }
    free(events);
    return 0;
}


