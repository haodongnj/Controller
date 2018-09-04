/*************************************************************
Author: Hao Dong
Date: 2018.06.23
Email:  hao.dong.nanjing@gmail.com
Note:   This is just a baseline implementation of simple 
        Repetitive Controller
*************************************************************/

#ifndef RC_H
#define RC_H
#define QVALUE 0.95f
#define NUM_SAMPLE_PER_CYCLE 200

extern float rc_buffer[NUM_SAMPLE_PER_CYCLE];

void Init_RC(void);
float Calc_RC(float sample);

#endif
