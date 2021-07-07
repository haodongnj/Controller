#ifndef FORC_H
#define FORC_H

#include <filter.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct FORC{
    float q_main ;
    float q_lr ;

    float *output_buffer ;
    float *delay_prev_buffer;
    float *input_buffer;

    int idx_q_input;
    int idx_q_output;
    int idx_prev;

    int max_steps_each_period;
    int f_control;

    int lead_steps ;
    Filter_t *p_compensator;
    float k ;

}FORC_t;

int index_forward(FORC_t s, int cur_index, int steps_forward);

void init_forc(FORC_t *s, float q_main, int lead_steps, float k, Filter* p_compensator);

float calc_forc(FORC_t *s, float error, float f);

#ifdef __cplusplus
};
#endif

#endif
