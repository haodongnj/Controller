/*************************************************************
Author: Hao Dong
Date: 2018.06.23
Email:  hao.dong.nanjing@gmail.com
Note:   This is just a baseline implementation of simple 
        Repetitive Controller
*************************************************************/

#include "rc.h"

float rc_buffer[NUM_SAMPLE_PER_CYCLE] ;

void Init_RC(void){
    int i = 0 ;
    for(i = 0; i < NUM_SAMPLE_PER_CYCLE; i++ ){
        rc_buffer[i] = 0.0f ;
    }
}

float Calc_RC(float sample){
    static int rc_counter = 0 ;
    float output = rc_buffer[rc_counter] ;

    // Simple implementation of Repetitive Controller 
    // when Q is a constant smaller than 1 ;
    rc_buffer[rc_counter] = QVALUE * (rc_buffer[rc_counter] + sample) ;

    rc_counter ++ ;
    if( rc_counter >= NUM_SAMPLE_PER_CYCLE){
        rc_counter = 0 ;
    }

    return output ;
}
