#include <rc.h>
#include <filter.h>
#include <stdio.h>
#include <math.h>

#define TS 1e-4 // 100us control period
#define NUM_ITERATIONS 20000 // 2 seconds

float rc_buffer1[200];
float rc_buffer2[200];
float rc_buffer3[200];

Filter_t compensator;
float filter_num[3] = {0, 0.00726436941467171, 0.00668055316076471};
float filter_den[3] = {1, -1.76382275659635, 0.777767679171789};
float x_buffer[4];
float y_buffer[4];

int main(){
    RC_t rc1;
    RC_t rc2;
    RC_t rc3;

    float output1 = 0.0f ;
    float output2 = 0.0f ;
    float output3 = 0.0f ;
    float sin_wave = 0.0f ;

    rc_init(&rc1, 0.9f, rc_buffer1, 200, 0, 1.0, NULL);
    rc_init(&rc2, 0.9f, rc_buffer2, 200, 25, 1.0, NULL);

    filter_init(&compensator, 2, filter_num, filter_den, x_buffer, y_buffer);
    rc_init(&rc3, 0.9f, rc_buffer3, 200, 50, 0.5, &compensator);

    FILE *fp = fopen("./test_rc_output.txt", "w+");
    if(fp == NULL){
        return -1;
    }

    for(int i = 0; i < NUM_ITERATIONS; i ++ ){
        sin_wave = sin( 2 * 3.1415926f * 50 * i * TS) ;
        output1 = rc_calc(&rc1, sin_wave) ;
        output2 = rc_calc(&rc2, sin_wave) ;
        output3 = rc_calc(&rc3, sin_wave) ;

        fprintf(fp, "%f\t%f\t%f\t%f\n", TS * i, output1, output2, output3);
    }

    fclose(fp) ;
    return 0 ;
}

