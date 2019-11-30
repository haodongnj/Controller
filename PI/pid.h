/*************************************************************
Author: Hao Dong
Email:  hao.dong.nanjing@outlook.com
*************************************************************/

#ifndef PID_H
#define PID_H

typedef struct {
    float kp ;
    float ki ;
    float ts ;
    float sum_ki ;
    float output ;
    float reference ;
} pidStruct;

void pid_init(pidStruct * s, float kp, float ki, float ts);
float pid_calc(pidStruct * s, float reference);

#endif
