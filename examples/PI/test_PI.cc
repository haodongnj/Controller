#include <PI.h>
#include <math.h>
#include <iostream>

#define NUMBER_ITERATIONS 200
#define PI 3.141592654f 
#define TS 1e-4

PI_t pi;

int main (void){
    float feedback = 0.0f ;
    float actuator = 0.0f ;

    pi_init(&pi, 1.0f, 10.0f, TS);

    FILE * fp = fopen("pi_results.txt", "w");

    for( int i = 0 ; i < NUMBER_ITERATIONS; i ++){
        feedback = sin(2 * PI * 50 * i * TS ) ;
        actuator = pi_calc(&pi, 1, feedback);
        fprintf(fp, "%f\t%f\r\n", i * TS, actuator) ;
    }

    fclose(fp) ;

    return 0 ;
}