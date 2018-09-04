#ifndef WDVRC_H
#define WDVRC_H

#include "../../filter/filter.h"
#include "math.h"

#define MAX_STEPS_FOR_BUFFER 205 
#define MIN_STEPS_FOR_BUFFER 196
#define STEPS_AT_BASE_FREQ 200

#define SLICE_ANGLE 0.031415927
#define DOUBLE_PI_DVRC 6.28318530718
#define PI_DVRC 3.14159265359

#define SIMULINK_DEBUG 1 


typedef struct dvrc_structure{
    double phase_buffer[MAX_STEPS_FOR_BUFFER] ;
    int phase_index ;
    double q_output_buffer[MAX_STEPS_FOR_BUFFER] ;
    int q_output_index ;
    double delay_prev_buffer[MAX_STEPS_FOR_BUFFER] ;
    int delay_prev_index ;

    int lead_steps ;
    filter_s * pfs ;
    double q_main ;
    double q_lr ;

    double weight_dm ; // delay 1 more step ; e.g. 202
    double weight_dl ; // delay 1 less step ; e.g. 201

    int error_flag  ;

}dvrc_struct ;

#if SIMULINK_DEBUG
void init_dvrc_simulink() ;
double calc_dvrc_simulink(double phase, double error, int flag_start_calc);
#endif

int find_varying_delay(dvrc_struct * ps, double cur_phase);
double compare_phase_angle(double cur_phase, double prev_phase) ;
int index_move(int cur_index, int steps_to_move);

#endif