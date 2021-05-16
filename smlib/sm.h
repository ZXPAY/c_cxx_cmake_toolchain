#ifndef SM_H
#define SM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct _sm_t {
    struct _sm_t *self;
    uint8_t state;
    void *map;
}sm_t;

typedef void (*sm_trans_func_t)(sm_t *sm, void *content);

typedef struct _mapping_t {
    sm_trans_func_t trans_cb;
    void *para;
}mapping_t;



#define ST_TRANS_MAP_START(sm_name)              \
    const mapping_t map_##sm_name[] = {
#define ST_TRANS_ENTRY(st_name, data_p)          \
    {.trans_cb=sm_trans##st_name, .para=data_p},
#define ST_TRANS_MAP_END(sm_name)                \
    };                                           \
    sm_##sm_name.map=(mapping_t *)&map_##sm_name;


#define sm_trans_def(st_name, sm_p, data_p) \
    void sm_trans ## st_name (sm_p, data_p)
#define sm_even(st_name, data)    \
    sm_trans ## st_name(data)

#define def_sm(sm_name, initial_state)  \
    sm_t sm_##sm_name = {.state=initial_state, .map=(mapping_t *)NULL}

#define concat_dot(obj, y) obj.y
#define sm_step(sm_name) \
    ((mapping_t *)sm_##sm_name.map)[concat_dot(sm_##sm_name, state)].trans_cb(&sm_##sm_name, ((mapping_t *)concat_dot(sm_##sm_name, map))[concat_dot(sm_##sm_name, state)].para)
    //((mapping_t *)sm_test.map)[0].trans_cb(&sm_test, ((mapping_t *)sm_test.map)[0].para);


#ifdef __cplusplus
extern "C" {
#endif

#endif /* SM_H */

