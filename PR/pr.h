/*************************************************************
Author: Hao Dong
Email:  hao.dong.nanjing@outlook.com
*************************************************************/

#ifndef CONTROLLER_PR_H_
#define CONTROLLER_PR_H_

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
float pr_calc(prStruct * s, float, float );

#endif /* ALGORITHM_CONTROLLER_PR_H_ */
