/*************************************************************
Author: Hao Dong
Date: 2018.06.23
Email:  hao.dong.nanjing@gmail.com
*************************************************************/

#include "pr.h"

void Init_prStruct(prStruct * s, float kp_set, float kr_set, float wi_set){
    s->kp = kp_set ;
    s->kr = kr_set ;
    s->wi = wi_set ;
    s->output_of_feedback = 0.0f ;
    s->output_of_backward_integrator = 0.0f ;
    s->output_of_forward_integrator = 0.0f ;
    s->reference = 0 ;
}

float Calc_prStruct(prStruct * s, float feedback, float wg){
    float error = s->reference - feedback ;

    float input_of_forward_integrator = 2 * s->wi * s->kr * error - s->output_of_feedback;
    // Forward integrator :
    s->output_of_forward_integrator += TS_Control *  input_of_forward_integrator;

    // Backward integrator:
    s->output_of_backward_integrator += TS_Control * s->output_of_forward_integrator * wg * wg ;

    s->output_of_feedback = s->output_of_backward_integrator + 2 * s->wi * s->output_of_forward_integrator ;

    return s->output_of_forward_integrator + s->kp * error;
}
