/*************************************************************
Author: Hao Dong
Date: 2018.06.23
Email:  hao.dong.nanjing@gmail.com
*************************************************************/

// This program is only a test demo on PC.
#include "pr.h"
#include "math.h"
#include "stdio.h"

int main(void){
    prStruct PR_Test ;
    float output = 0.0f , sin_wave = 0.0f ;
    FILE * fp ;
    fp = fopen("./PR_Outputs.txt", "w+");

    Init_prStruct(&PR_Test, 0.0f, 10.0f, 6.28f);
    for(int i = 0 ; i < 100000; i ++ ){
        sin_wave = sin( 2 * 3.1415926 * 50 * i * TS_Control) ;
        output = Calc_prStruct(&PR_Test, sin_wave, 2 * 3.1415926 * 50.0) ;
        fprintf(fp, "%lf\t%lf\n", TS_Control * i, output);
    }
    fclose(fp) ;
    return 0 ;
}
