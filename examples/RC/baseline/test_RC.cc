#include <rc.h>
#include <stdio.h>
#include <math.h>

#define TS_Control 1e-4 // 100us control period
#define NUM_ITERATIONS 20000 // 2 seconds

float rc_buffer[200];

int main(){
    RC_t rc;
    float output = 0.0f , sin_wave = 0.0f ;

    rc_init(&rc, 0.9f, rc_buffer, 200);

    FILE *fp = fopen("./test_rc_output.txt", "w+");

    for(int i = 0; i < NUM_ITERATIONS; i ++ ){
        sin_wave = sin( 2 * 3.1415926f * 50 * i * TS_Control) ;
        output = rc_calc(&rc, sin_wave) ;

        fprintf(fp, "%f\t%f\n", TS_Control * i, output);
    }

    fclose(fp) ;
    return 0 ;
}

