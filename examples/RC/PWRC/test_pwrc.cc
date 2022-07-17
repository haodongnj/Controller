#include <pwrc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TS 5e-5 // 50us control period
#define PWRC_DOUBLE_PI  6.283185307179586f

Filter_t compensator;
float filter_num[3] = {0.01979, 0.03958, 0.01979};
float filter_den[3] = {1, -1.565, 0.6437};
float x_buffer[3];
float y_buffer[3];

// just use more memory than needed for illustration
#define PWRC_BUF_SIZE 425
float delay_buf[PWRC_BUF_SIZE];
float q_output_buf[PWRC_BUF_SIZE];
float phase_buf[PWRC_BUF_SIZE];

int main(void){

  FILE * fp_out = fopen("test_pwrc_output.txt", "w") ;
  if(fp_out == NULL){
    printf("Error creating file\r\n") ;
    exit(0) ;
  }

  PWRC_t pwrc;
  float rc_output, sin_wave ;
  float phase = 0.0f;

  filter_init(&compensator, 2, filter_num, filter_den, x_buffer, y_buffer);
  init_pwrc(&pwrc, delay_buf, q_output_buf, phase_buf, PWRC_BUF_SIZE, 11, 1.0, 0.9, &compensator);

  // 50 Hz nominal grid frequency
  for( int i = 0 ; i < 1000; i ++){
    float time = i * TS;
    phase += 2.0f * 3.1415926f * 50.0f * TS;
    if(phase > PWRC_DOUBLE_PI){
      phase -= PWRC_DOUBLE_PI;
    }
    sin_wave = sin(phase) ;
    rc_output = calc_pwrc(&pwrc, sin_wave, phase, 0);
    fprintf(fp_out, "%f,%f,%f\n", time, 0, rc_output) ;
  }

  // 49.5 Hz grid frequency
  for( int i = 1000 ; i < 5000; i ++){
    float time = i * TS;
    phase += 2.0f * 3.1415926f * 49.5f * TS;
    if(phase > PWRC_DOUBLE_PI){
      phase -= PWRC_DOUBLE_PI;
    }
    sin_wave = sin(phase) ;
    rc_output = calc_pwrc(&pwrc, sin_wave, phase, 1);
    fprintf(fp_out, "%f,%f,%f\n", time, sin_wave, rc_output) ;
  }

  // 50.5 Hz grid frequency
  for( int i = 5000 ; i < 10000; i ++){
    float time = i * TS;
    phase += 2.0f * 3.1415926f * 50.5f * TS;
    if(phase > PWRC_DOUBLE_PI){
      phase -= PWRC_DOUBLE_PI;
    }
    sin_wave = sin(phase) ;
    rc_output = calc_pwrc(&pwrc, sin_wave, phase, 1);
    fprintf(fp_out, "%f,%f,%f\n", time, sin_wave, rc_output) ;
  }

  fclose(fp_out) ;
  return 0 ;
}