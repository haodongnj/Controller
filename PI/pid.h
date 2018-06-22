#ifndef PID_H
#define PID_H
#define PID_KD_ENABLED 0

#define T_CONTROL 0.0001f // 10kHz control period

typedef struct {
    float kp ;
    float ki ;
#if PID_KD_ENABLED
    float kd ;
#endif
    float sum_ki ;
    float output ;
    float reference ;
} pidStruct;

void Init_pidStruct(pidStruct * s, float, float) ;
float Calc_pidStruct(pidStruct * s, float reference);

#endif
