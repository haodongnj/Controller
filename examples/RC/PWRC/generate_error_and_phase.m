close all ;
clear ;
clc ;

freq = 1e4/200.2  ;
samples_f = 1e4 / freq ; 
samples = int32(1e4 / freq);

t = 1e-4:1e-4:1e2 ; 
ph = 2 * pi * freq * t ;

ph = mod(ph, 2*pi) ;

error = sin(ph) ;
figure ;
plot(t, error) ;
figure ;
plot(t, ph) ;

data = [error', ph'] ;
dlmwrite('test_error_phase.txt', data) ;

 