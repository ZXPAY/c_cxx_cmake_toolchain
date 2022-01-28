#ifndef RELIEVE_STRESS_H
#define RELIEVE_STRESS_H

#include <stdint.h>

#define MAX_RELIEVE_REGISTER        (12)
#define RELIEVE_PASS                (0x80)
#define RELIEVE_NO_CHOOSE           (0xFF)


typedef struct _relieve_unit_t {
    uint8_t pos;
    uint8_t value;
    uint8_t action;
} relieve_unit_t;

typedef enum {
    RELIEVE_TIME_MODE = 0,
    RELIEVE_SENSOR_MODE = 1
} relieve_em;

typedef enum {
    RELIVE_NOCHANGE = 0,
    RELIEVE_INFLATE = 1,
    RELIEVE_DEFLATE = 2
} relieve_act_em;

typedef struct _relieve_stress_t {
    uint8_t count;
    uint8_t current_index;
    relieve_em mode;
    uint32_t tick;
    uint8_t state;
    relieve_unit_t relieve_unit[MAX_RELIEVE_REGISTER];
} relieve_stress_t;

void reset_relieve_stress(relieve_stress_t *relieve_stress);
void reset_state_relieve_stress(relieve_stress_t *relieve_stress);
void set_relieve_stress_mode(relieve_stress_t *relieve_stress, relieve_em mode);
void register_relieve_stress(relieve_stress_t *relieve_stress, uint8_t pos, uint8_t value, relieve_act_em act);
void insert_relieve_stress(relieve_stress_t *relieve_stress, uint8_t index, uint8_t pos, uint8_t value, relieve_act_em act);
uint8_t get_current_index(relieve_stress_t *relieve_stress);
uint8_t get_register_count(relieve_stress_t *relieve_stress);
relieve_em get_relieve_mode(relieve_stress_t *relieve_stress);
uint8_t is_next_pos(relieve_stress_t *relieve_stress);

#endif /* RELIEVE_STRESS_H */
