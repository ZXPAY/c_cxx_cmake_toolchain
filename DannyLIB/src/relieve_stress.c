#include "stdint.h"
#include "relieve_stress.h"
#include <time.h>

static uint8_t state = 0;
static uint8_t current_index = 0;
static uint32_t tick = 0;

relieve_stress_t relieve_stress = {   \
    .count = 0,                       \
    .mode = RELIEVE_TIME_MODE,        \
    .relieve_unit = {0}               \
};


__attribute__((weak)) int get_tick(void) {
    return time(NULL)*1000;
}

void register_relieve_stress(uint8_t pos, uint8_t value, relieve_act_em act) {
    if(relieve_stress.count >= MAX_RELIEVE_REGISTER) return;

    relieve_stress.relieve_unit[relieve_stress.count].pos = pos;
    relieve_stress.relieve_unit[relieve_stress.count].value = value;
    relieve_stress.relieve_unit[relieve_stress.count].action = act;
    relieve_stress.count++;
}

void insert_relieve_stress(uint8_t index, uint8_t pos, uint8_t value, relieve_act_em act) {
    if(index >= MAX_RELIEVE_REGISTER) return;

    relieve_stress.relieve_unit[index].pos = pos;
    relieve_stress.relieve_unit[index].value = value;
    relieve_stress.relieve_unit[index].action = act;
}

inline uint8_t get_register_count(void) {
    return relieve_stress.count;
}

inline relieve_em get_relieve_mode(void) {
    return relieve_stress.mode;
}

inline uint8_t get_current_index(void) {
    return current_index;
}

uint8_t is_next_pos(void) {    
    if(0 == state) {
        tick = get_tick();
        if(relieve_stress.count > 0 && relieve_stress.count > current_index) {
            state = 1;
            return current_index;
        } 
    }
    else if((get_tick() - tick) / 1000 > (relieve_stress.relieve_unit[current_index].value&0x7F) ||
            (relieve_stress.relieve_unit[current_index].value & RELIEVE_PASS)) {
        current_index++;
        if(current_index == relieve_stress.count) current_index = 0;
        state = 0;
    }


    return 0xFF;
}




