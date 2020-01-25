/*************************************************************
Author: Hao Dong
Email:  hao.dong.nanjing@outlook.com
*************************************************************/

// This program is a test demo on PC.
#include "../pr.h"
#include "math.h"
#include "stdio.h"

#define TS_Control 1e-4 // 100us control period

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
    prStruct PR_Test ;
    float output = 0.0f , sin_wave = 0.0f ;
    FILE * fp ;
    fp = fopen("./test_pr_output.txt", "w+");

    pr_init(&PR_Test, 0.0f, 10.0f, 6.28f, TS_Control);
    for(int i = 0 ; i < 100000; i ++ ){
        sin_wave = sin( 2 * 3.1415926 * 50 * i * TS_Control) ;
        output = pr_calc(&PR_Test, sin_wave, 2 * 3.1415926 * 50.0) ;
        fprintf(fp, "%f\t%f\n", TS_Control * i, output);
    }
    fclose(fp) ;
    return 0 ;
}
