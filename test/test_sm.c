#include <sm.h>
#include <stdio.h>
#include <stdint.h>

enum STATE {
    A,
    B,
    C
};

typedef uint8_t var_A_t;
typedef uint8_t var_B_t;
typedef struct _var_C_t {
    uint8_t var1;
    uint8_t var2;
}var_C_t;


int flag = 0;

sm_trans_def(A, sm_t *sm, void *para) {
    var_A_t *data = (var_A_t *)para;
    printf("state A, %d\n", *data);
    (*data)++;
    if(*data > 2) {
        // go to state B
        sm->state = B;
    }
};

sm_trans_def(B, sm_t *sm, void *para){
    var_B_t *data = (var_B_t *)para;
    printf("state B, %d\n", *data);
    (*data)++;
    if(*data > 5) {
        sm->state = C;
    }
};

sm_trans_def(C, sm_t *sm, void *para){
    var_C_t *data = (var_C_t *)para;
    printf("state C\n");
    data->var1++;
    data->var2++;
    if(data->var1 == 2 && data->var2==2) {
        sm->state = A;
    }
}

;

void step(sm_t *sm) {
    printf("step: %d\n", sm->state);
    
}


int main(int argv, char *argc[]) {
    printf("state: %d\n", 1);
    var_A_t data_a = 0;
    var_B_t data_b = 0;
    var_C_t data_c = {.var1=0, .var2=0};
    
    // Define the state machine object
    def_sm(test, A);

    ST_TRANS_MAP_START(test)
    ST_TRANS_ENTRY(A, (var_A_t *)&data_a)
    ST_TRANS_ENTRY(B, (var_B_t *)&data_b)
    ST_TRANS_ENTRY(C, (var_C_t *)&data_c)
    ST_TRANS_MAP_END(test)

       
    // printf("%p\n", &map_test); 
    // printf("%p\n", sm_test.map); 
    // printf("%p\n", ((mapping_t *)sm_test.map)[0].trans_cb(&sm_test, ((mapping_t *)sm_test.map)[0].para));
    
    for(int i=0;i<20;i++) {
        sm_step(test);
    }
    return 0;
}



