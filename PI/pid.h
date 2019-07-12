/*************************************************************
Author: Hao Dong
Date: 2018.06.23
Email:  hao.dong.nanjing@outlook.com
*************************************************************/

#ifndef PID_H
#define PID_H

typedef struct {
    double kp ;
    double ki ;
    double ts ;
    double sum_ki ;
    double output ;
    double reference ;
} pidStruct;

void Init_pidStruct(pidStruct * s, double kp, double ki, double ts);
double Calc_pidStruct(pidStruct * s, double reference);

#endif
