#include <filter.h>
#include <math.h>
#include <iostream>

#define NUMBER_ITERATIONS 200
#define PI 3.141592654f 
#define TS 1e-4

/**
 * The coefficients corresponds to the following filter:
 *  0.007264 z + 0.006681
 * ----------------------
 *  z^2 - 1.764 z + 0.7778
 * which is then validated by Octave/MATLAB
**/

Filter_t lp_filter ;
float filter_num[3] = {0, 0.00726436941467171, 0.00668055316076471};
float filter_den[3] = {1, -1.76382275659635, 0.777767679171789};
float x_buffer[3];
float y_buffer[3];

int main (void){
    float input_sine = 0.0f ; 
    float output_sin = 0.0f ;
    filter_init(&lp_filter, 2, filter_num, filter_den, x_buffer, y_buffer);

    FILE * fp = fopen("filter_results.txt", "w");

    for( int i = 0 ; i < NUMBER_ITERATIONS; i ++){
        input_sine = sin(2 * PI * 50 * i * TS ) ;
        output_sin = filter_calc(&lp_filter, input_sine);
        fprintf(fp, "%f\t%f\r\n", i * TS, output_sin) ;
    }
    fclose(fp) ;

    return 0 ;
}