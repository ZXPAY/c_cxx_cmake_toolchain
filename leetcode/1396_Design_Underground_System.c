#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define MAX_CUSTOM          (20000)

typedef enum _travel_state_em_ {
    UNDETERMINED = 0,
    CHECKIN = 1,
    CHECKOUT = 2,
} travel_state_em;

typedef struct {
    int id;
    char *station_checkin;
    char *station_checkout;
    travel_state_em state;
    int t_checkin;
    int t_checkout;
    int travel_time;
} custom_t;

typedef struct {
    custom_t *customs[MAX_CUSTOM];
    int custom_count;
} UndergroundSystem;


custom_t *generate_custom(int id, char *station_name, int t_checkin) {
    custom_t *new_custom = malloc(sizeof(custom_t));
    memset(new_custom, 0, sizeof(custom_t));
    // copy station name
    int station_name_len = strlen(station_name) + 1;
    new_custom->station_checkin = malloc(station_name_len*sizeof(char));
    memcpy(new_custom->station_checkin, station_name, station_name_len*sizeof(char));

    new_custom->id = id;
    new_custom->state = CHECKIN;
    new_custom->t_checkin = t_checkin;

    return new_custom;    
}

void help_custom_checkout(custom_t *custom, char *station_name, int t_checkout) {
    // copy station name
    int station_name_len = strlen(station_name) + 1;
    custom->station_checkout = malloc(station_name_len*sizeof(char));
    memcpy(custom->station_checkout, station_name, station_name_len*sizeof(char));

    custom->t_checkout = t_checkout;
    custom->state = CHECKOUT;
    custom->travel_time = custom->t_checkout - custom->t_checkin;
}

UndergroundSystem *undergroundSystemCreate() {
    UndergroundSystem *underground_system = malloc(sizeof(UndergroundSystem));
    memset(underground_system, 0, sizeof(UndergroundSystem));

    return underground_system;
}

void undergroundSystemCheckIn(UndergroundSystem *obj, int id, char *stationName, int t) {
    obj->customs[obj->custom_count++] = generate_custom(id, stationName, t);
}

void undergroundSystemCheckOut(UndergroundSystem *obj, int id, char *stationName, int t) {
    for(int i=0;i<obj->custom_count;i++) {
        if(obj->customs[i]->state == CHECKIN && id == obj->customs[i]->id) {
            help_custom_checkout(obj->customs[i], stationName, t);
            return;
        }
    }
}

double undergroundSystemGetAverageTime(UndergroundSystem *obj, char *startStation, char *endStation) {
    int count = 0;
    double sum = 0.0;
    for(int i=0;i<obj->custom_count;i++) {
        if(obj->customs[i]->state != CHECKOUT) {
            continue;
        }
        if(strncmp(obj->customs[i]->station_checkin, startStation, strlen(startStation)) == 0 &&
            strncmp(obj->customs[i]->station_checkout, endStation, strlen(endStation)) == 0) {
                count++;
                sum += (double)obj->customs[i]->travel_time;
        }
    }

    if(count == 0) return 0.0;
    return sum / (double)count;
}

void undergroundSystemFree(UndergroundSystem *obj) {
    for(int i=0;i<obj->custom_count;i++) {
        free(obj->customs[i]);
    }
    free(obj);
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    UndergroundSystem* obj = undergroundSystemCreate();
    undergroundSystemCheckIn(obj, 45, "Leyton", 3);
    undergroundSystemCheckIn(obj, 32, "Paradise", 8);
    undergroundSystemCheckIn(obj, 27, "Leyton", 10);
    undergroundSystemCheckOut(obj, 45, "Waterloo", 15);  // id 45: 15 - 3 = 12
    undergroundSystemCheckOut(obj, 27, "Waterloo", 20);  // id 27: 20 - 10 = 10
    undergroundSystemCheckOut(obj, 32, "Cambridge", 22); // id 32: 22 - 8 = 14
    double avg_p_c = undergroundSystemGetAverageTime(obj, "Paradise", "Cambridge");  // return 14.000
    double avg_l_w = undergroundSystemGetAverageTime(obj, "Leyton", "Waterloo");     // return 11.000  (12+10)/2

    printf("averge time Paradise(ans=14) -> Cambridge: %.2f\n", avg_p_c);
    printf("averge time Leyton(ans=11) -> Waterloo: %.2f\n", avg_l_w);
    
    undergroundSystemCheckIn(obj, 10, "Leyton", 24);
    avg_l_w = undergroundSystemGetAverageTime(obj, "Leyton", "Waterloo");     // return 11.000  (12+10)/2
    printf("should be 11: %.2f\n", avg_l_w);
    undergroundSystemCheckOut(obj, 10, "Waterloo", 38);  // id 10: 38 - 24 = 14
    avg_l_w = undergroundSystemGetAverageTime(obj, "Leyton", "Waterloo");     // return 12.000  (12+10+14)/3
    printf("averge time Leyton(ans=12) -> Waterloo: %.2f\n", avg_l_w);

    undergroundSystemFree(obj);
}

