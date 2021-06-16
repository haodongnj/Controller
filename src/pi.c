#include <pi.h>

void pi_init(PI_t * s, float kp, float ki, float ts) {
    s->kp = kp ;
    s->ts = ts ;
    s->ki = ki * ts ;
    s->sum_ki = 0.0f ;
    s->output = 0.0f ;
    s->reference = 0.0f ;
}

float pi_calc(PI_t *s, float reference, float feedback) {
    s->reference = reference;
    float error = s->reference - feedback ;
    s->sum_ki += s->ki * error ;
    s->output = s->sum_ki + s->kp * error ;
    return s->output ;
}
