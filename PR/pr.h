/*************************************************************
Author: Hao Dong
Email:  hao.dong.nanjing@outlook.com
*************************************************************/

#ifndef PR_H
#define PR_H

typedef struct{
    float kp ;
    float kr ;
    float wi ;
    float reference ;
    float ts ;
    float output_of_backward_integrator ;
    float output_of_feedback ;
    float output_of_forward_integrator ;
    float last_input_of_forward_integrator ;
}prStruct;

void pr_init(prStruct * s, float, float, float, float) ;
void pr_update_ref(prStruct * s, float ref);
float pr_calc(prStruct * s, float, float );

#endif
