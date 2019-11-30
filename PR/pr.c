/*************************************************************
Author: Hao Dong
Email:  hao.dong.nanjing@outlook.com
*************************************************************/

#include "pr.h"

void pr_init(prStruct * s, float kp_set, float kr_set, float wi_set, float ts){
    s->kp = kp_set ;
    s->kr = kr_set ;
    s->wi = wi_set ;
    s->ts = ts ;
    s->output_of_feedback = 0.0f ;
    s->output_of_backward_integrator = 0.0f ;
    s->output_of_forward_integrator = 0.0f ;
    s->reference = 0.0f ;
}

/**
 * Second Order Generalized Integratior(SOGI) implementation for frequency adaptive resonance controller
**/
float pr_calc(prStruct * s, float feedback, float wg){
    float error = s->reference - feedback ;

    float input_of_forward_integrator = 2 * s->wi * s->kr * error - s->output_of_feedback;
    // Forward integrator :
    s->output_of_forward_integrator += s->ts *  input_of_forward_integrator;

    // Backward integrator:
    s->output_of_backward_integrator += s->ts * s->output_of_forward_integrator * wg * wg ;

    s->output_of_feedback = s->output_of_backward_integrator + 2 * s->wi * s->output_of_forward_integrator ;

    return s->output_of_forward_integrator + s->kp * error;
}
