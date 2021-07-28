#include <forc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TS 1e-4 // 100us control period

Filter_t compensator;
float filter_num[3] = {0, 0.00726436941467171, 0.00668055316076471};
float filter_den[3] = {1, -1.76382275659635, 0.777767679171789};
float x_buffer[4];
float y_buffer[4];

int main(void){

    FILE * fp_out = fopen("text_output.txt", "w") ;
    if(fp_out == NULL){ 
        printf("Error creating file\r\n") ;
        exit(0) ;
    }

    FORC_t forc;
    float freq, rc_output, sin_wave ;
    float buffer[420];
    filter_init(&compensator, 2, filter_num, filter_den, x_buffer, y_buffer);
    init_forc(&forc, 0.9, buffer, 410, 25, 1.0, &compensator, 1e4);

    for( int i = 0 ; i < 10e4 ; i ++){
        sin_wave = sin( 2 * 3.1415926 * 49.5 * i * TS) ;
        rc_output = calc_forc(&forc, sin_wave, 49.5);
        fprintf(fp_out, "%f\r\n", rc_output) ;
    }

    fclose(fp_out) ;
    return 0 ;
}