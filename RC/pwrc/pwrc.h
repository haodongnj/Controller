#ifndef WDVRC_H
#define WDVRC_H

#include "../../filter/filter.h"
#include "math.h"

#define USE_TEN_KHZ 0
#define USE_TWENTY_KHZ 1

#if USE_TEN_KHZ
#define SLICE_ANGLE 0.0314159265359
#define MAX_STEPS_FOR_BUFFER 205
#define MIN_STEPS_FOR_BUFFER 196
#define STEPS_AT_BASE_FREQ 200
#endif
#if USE_TWENTY_KHZ
#define SLICE_ANGLE 0.01570796326795
#define MAX_STEPS_FOR_BUFFER 410
#define MIN_STEPS_FOR_BUFFER 392
#define STEPS_AT_BASE_FREQ 400
#endif


#define DOUBLE_PI_DVRC 6.28318530718
#define PI_DVRC 3.14159265359

#define SIMULINK_DEBUG 0

#if SIMULINK_DEBUG
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

    double krc ;
    double weight_dm ; // delay 1 more step ; e.g. 202
    double weight_dl ; // delay 1 less step ; e.g. 201

    int error_flag  ;

}dvrc_struct ;

void init_wdvrc_simulink() ;
double calc_wdvrc_simulink(double phase, double error, int flag_start_calc);
int find_varying_delay(dvrc_struct * ps, double cur_phase);
double compare_phase_angle(double cur_phase, double prev_phase) ;
int index_move(int cur_index, int steps_to_move);

#else

typedef struct dvrc_structure{
    float phase_buffer[MAX_STEPS_FOR_BUFFER] ;
    int phase_index ;
    float q_output_buffer[MAX_STEPS_FOR_BUFFER] ;
    int q_output_index ;
    float delay_prev_buffer[MAX_STEPS_FOR_BUFFER] ;
    int delay_prev_index ;

    int lead_steps ;
    filter_s * pfs ;
    float q_main ;
    float q_lr ;

    float krc ;
    float weight_dm ; // delay 1 more step ; e.g. 202
    float weight_dl ; // delay 1 less step ; e.g. 201

    int error_flag  ;

}dvrc_struct ;

void init_wdvrc(dvrc_struct * p_dvrc_s, filter_s * p_f_s, float q_main,  float k_rc, int steps_lead);
float calc_wdvrc(dvrc_struct * p_dvrc_s, float phase, float error, int flag_start_calc);
int find_varying_delay(dvrc_struct * ps, float cur_phase);
float compare_phase_angle(float cur_phase, float prev_phase) ;
int index_move(int cur_index, int steps_to_move);

#endif

#endif
