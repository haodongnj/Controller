// #include "rc_interpolation.h"
#include "irc.h"
#include "stdio.h"

int main(void){
    FILE * fp_in = fopen("test_data.txt", "r") ;
    FILE * fp_out = fopen("test_output.txt", "w");
    irc_init_simulink();
    double error, phase, output ;
    printf("Init completed.\r\n");
    for(int i = 0 ; i < 2000 ; i ++ ){
        printf("Read data from file.\r\n");
        fscanf(fp_in, "%lf,%lf\n", &error, &phase);
        printf("Error:%lf\tPhase:%lf\r\n", error, phase) ;
        output = irc_update_simulink(error, phase) ;
        printf("%lf\r\n", output) ;
        fprintf(fp_out, "%lf\r\n", output);
    }
    fclose(fp_in);
    fclose(fp_out);
}