#include "filter.h"
#include "math.h"
#include "stdio.h"

#define NUMBER_ITERATIONS 1e4 
#define PI 3.141592654f 
#define TS 1e-4

filter_s lp_filter ;
double filter_num[3] = {0, 0.00726436941467171, 0.00668055316076471};
double filter_den[3] = {1, -1.76382275659635, 0.777767679171789};


int main (void){
    double input_sine = 0.0f ; 
    double output_sin = 0.0f ;
    filter_init(&lp_filter, filter_num, filter_den, 2);

    FILE * fp = fopen("filter_results.txt", "w");

    for( int i = 0 ; i < NUMBER_ITERATIONS; i ++){
        input_sine = sin(2 * PI * 50 * i * TS ) ;
        output_sin = filter_calc(&lp_filter, input_sine);
        fprintf(fp, "%f\t%f\r\n", i * TS, output_sin) ;
    }
    fclose(fp) ;

    return 0 ;
}