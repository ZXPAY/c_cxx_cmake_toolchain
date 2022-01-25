#ifndef RELIEVE_STRESS_H
#define RELIEVE_STRESS_H

#include <stdint.h>

#define MAX_RELIEVE_REGISTER        12
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
    RELIEVE_INFLATE = 0,
    RELIEVE_DEFLATE = 1
} relieve_act_em;

typedef struct _relieve_stress_t {
    uint8_t count;
    relieve_em mode;
    relieve_unit_t relieve_unit[MAX_RELIEVE_REGISTER];
} relieve_stress_t;


void register_relieve_stress(uint8_t pos, uint8_t value, relieve_act_em act);
void insert_relieve_stress(uint8_t index, uint8_t pos, uint8_t value, relieve_act_em act);
uint8_t get_current_index(void);
uint8_t get_register_count(void);
relieve_em get_relieve_mode(void);
uint8_t is_next_pos(void);

#endif /* RELIEVE_STRESS_H */
