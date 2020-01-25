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
void pid_update_ref(pidStruct * s, float ref);
float pid_calc(pidStruct * s, float feedback);

#endif
