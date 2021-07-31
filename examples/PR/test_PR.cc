// This program is a test demo on PC.
#include <math.h>
#include <pr.h>
#include <stdio.h>

#define TS_Control 1e-4 // 100us control period
#define NUM_ITERATIONS 20000 // 2 seconds

/**
 * @brief Test output of the PR controller
 *      kp :    0.0 
 *      kr :    10.0
 *      wi :    2% of wg, 2% * 50 * 2 * 3.14 = 6.28 
 *      Input : sine signal, 50Hz, with an amplitude of 1 
 *      Output :    sine signal, 50Hz, with an static amplitude of 10
 * @return int 
 */
int main(void){
    PR_t pr;
    float output = 0.0f , sin_wave = 0.0f ;
    FILE * fp ;
    fp = fopen("./test_pr_output.txt", "w+");

    pr_init(&pr, 0.0f, 10.0f, 6.28f, TS_Control);
    for(int i = 0 ; i < NUM_ITERATIONS; i ++ ){
        sin_wave = sin( 2 * 3.1415926 * 50 * i * TS_Control) ;
        output = pr_calc(&pr, sin_wave, 0, 2 * 3.1415926 * 50.0) ;
        fprintf(fp, "%f\t%f\n", TS_Control * i, output);
    }
    fclose(fp) ;
    return 0 ;
}
