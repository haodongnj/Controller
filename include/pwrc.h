#ifndef WDVRC_H
#define WDVRC_H

#include <filter.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#define PWRC_DOUBLE_PI (M_PI * 2)

#ifdef __cplusplus
extern "C"{
#endif

typedef struct PWRC{
    float q_main ;
    float q_lr ;

    float phase_buffer[MAX_STEPS_FOR_BUFFER] ;
    int phase_index ;
    float q_output_buffer[MAX_STEPS_FOR_BUFFER] ;
    int q_output_index ;
    float delay_prev_buffer[MAX_STEPS_FOR_BUFFER] ;
    int delay_prev_index ;

    int lead_steps ;
    filter_s * pfs ;

    float krc ;
    float weight_dm ; // delay 1 more step ; e.g. 202
    float weight_dl ; // delay 1 less step ; e.g. 201

    int error_flag  ;

}PWRC_t;

void init_pwrc(dvrc_struct * p_dvrc_s, filter_s * p_f_s, float q_main,  float k_rc, int steps_lead);
float calc_pwrc(dvrc_struct * p_dvrc_s, float phase, float error, int flag_start_calc);
int find_varying_delay(dvrc_struct * ps, float cur_phase);
float compare_phase_angle(float cur_phase, float prev_phase) ;

int index_forward(int cur_index, int steps_to_move);

#ifdef __cplusplus
};
#endif

#endif

