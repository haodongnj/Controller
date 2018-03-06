#ifndef RC_H
#define RC_H
#define QVALUE 0.95f

extern float rc_buffer[200];

void Init_RC(void);
float Calc_RC(float sample);

#endif