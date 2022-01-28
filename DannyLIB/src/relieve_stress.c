#include <stdbool.h>
#include <time.h>
#include "stdint.h"
#include "relieve_stress.h"

#define PRESSURE_LEVELS     10
#define MATTRESS_SENSOR_NUM 12

const uint32_t pressure_level[PRESSURE_LEVELS] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};


extern const uint8_t mattress_sensor_index_map[MATTRESS_SENSOR_NUM];

__attribute__((weak)) int get_tick() {
    return time(NULL);
}

__attribute__((weak)) uint32_t get_sensor(uint8_t index) {
    return 1;
}

void reset_relieve_stress(relieve_stress_t *relieve_stress) {
    relieve_stress->current_index = 0;    
    relieve_stress->count = 0;    
    relieve_stress->state = 0;    
}

void reset_state_relieve_stress(relieve_stress_t *relieve_stress) {
    relieve_stress->current_index = 0;    
    relieve_stress->state = 0;    
}

void set_relieve_stress_mode(relieve_stress_t *relieve_stress, relieve_em mode) {
    relieve_stress->mode = mode;
}

void register_relieve_stress(relieve_stress_t *relieve_stress, uint8_t pos, uint8_t value, relieve_act_em act) {
    if(relieve_stress->count >= MAX_RELIEVE_REGISTER) return;

    relieve_stress->relieve_unit[relieve_stress->count].pos = pos;
    relieve_stress->relieve_unit[relieve_stress->count].value = value;
    relieve_stress->relieve_unit[relieve_stress->count].action = act;
    relieve_stress->count++;
}

void insert_relieve_stress(relieve_stress_t *relieve_stress, uint8_t index, uint8_t pos, uint8_t value, relieve_act_em act) {
    if(index >= MAX_RELIEVE_REGISTER) return;

    relieve_stress->relieve_unit[index].pos = pos;
    relieve_stress->relieve_unit[index].value = value;
    relieve_stress->relieve_unit[index].action = act;
}

inline uint8_t get_register_count(relieve_stress_t *relieve_stress) {
    return relieve_stress->count;
}

inline relieve_em get_relieve_mode(relieve_stress_t *relieve_stress) {
    return relieve_stress->mode;
}

inline uint8_t get_current_index(relieve_stress_t *relieve_stress) {
    return relieve_stress->current_index;
}

uint8_t is_next_pos(relieve_stress_t *relieve_stress) {    
    int pos = relieve_stress->relieve_unit[relieve_stress->current_index].pos;
    bool flag = false;

    if(0 == relieve_stress->state) {
        if(relieve_stress->count > 0 && relieve_stress->count > relieve_stress->current_index) {
            relieve_stress->state = 1;
            if(RELIEVE_SENSOR_MODE == relieve_stress->mode) {
                relieve_stress->tick = 0;
            }
            else {
                relieve_stress->tick = get_tick();
            }
            return relieve_stress->current_index;
        }
    }
    else if(RELIEVE_TIME_MODE == relieve_stress->mode) {
        if((get_tick() - relieve_stress->tick) > (relieve_stress->relieve_unit[relieve_stress->current_index].value&0x7F) ||
            (relieve_stress->relieve_unit[relieve_stress->current_index].value & RELIEVE_PASS)) {
            relieve_stress->current_index++;
            if(relieve_stress->current_index == relieve_stress->count) relieve_stress->current_index = 0;
            relieve_stress->state = 0;
        }
    }
    else if(RELIEVE_SENSOR_MODE == relieve_stress->mode) {
        if((relieve_stress->relieve_unit[relieve_stress->current_index].value&0x1F) >= 20) {
            return RELIEVE_NO_CHOOSE;
        }
        if(pos >= 12) {
            return RELIEVE_NO_CHOOSE;
        }

        uint32_t pressure = pressure_level[relieve_stress->relieve_unit[relieve_stress->current_index].value&0x1F];
        uint32_t sensor_pressure = get_sensor(pos);

        // timeout 20 seconds
        if(relieve_stress->tick++ > 500) {
            flag = true;
        }

        if(relieve_stress->relieve_unit[relieve_stress->current_index].value & RELIEVE_PASS) {
            flag = true;
        }
        else if(RELIEVE_INFLATE == relieve_stress->relieve_unit[relieve_stress->current_index].action &&
            sensor_pressure > pressure) {
            flag = true;
        }
        else if(RELIEVE_DEFLATE == relieve_stress->relieve_unit[relieve_stress->current_index].action &&
            sensor_pressure < pressure) {
            flag = true;
        }

        if(flag) {
            relieve_stress->current_index++;
            if(relieve_stress->current_index == relieve_stress->count) relieve_stress->current_index = 0;
            relieve_stress->state = 0;
            relieve_stress->tick = 0;
        }
    }

    return RELIEVE_NO_CHOOSE;
}
