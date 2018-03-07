#ifndef RC_H
#define RC_H
#define QVALUE 0.95f
#define NUM_SAMPLE_PER_CYCLE 200

extern float rc_buffer[NUM_SAMPLE_PER_CYCLE];

void Init_RC(void);
float Calc_RC(float sample);

#endif
