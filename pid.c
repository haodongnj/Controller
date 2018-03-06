#include "pid.h"

void Init_pidStruct(pidStruct * s, float kp, float ki) {
    s->kp = kp ;
    s->ki = ki ;
    s->sum_ki = 0 ;
    s->output = 0 ;
    s->reference = 0 ;
}

float Calc_pidStruct(pidStruct * s, float feedback) {
    float error = s->reference - feedback ;
    s->sum_ki = s->ki * error ;
    s->output = s->sum_ki + s->kp * error ;
    return s->output ;
}
