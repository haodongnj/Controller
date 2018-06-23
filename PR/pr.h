/*************************************************************
Author: Hao Dong
Date: 2018.06.23
Email:  hao.dong.nanjing@gmail.com
*************************************************************/

#ifndef ALGORITHM_CONTROLLER_PR_H_
#define ALGORITHM_CONTROLLER_PR_H_

#define TS_Control 1e-4 // 100us control period

typedef struct{
    float kp ;
    float kr ;
    float wi ;
    float reference ;
    float output_of_backward_integrator ;
    float output_of_feedback ;
    float output_of_forward_integrator ;
    float last_input_of_forward_integrator ;
}prStruct;

void Init_prStruct(prStruct * s, float, float, float) ;
float Calc_prStruct(prStruct * s, float, float );

#endif /* ALGORITHM_CONTROLLER_PR_H_ */
