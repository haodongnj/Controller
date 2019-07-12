close all ;
clear ;
clc ;

freq = 2e4/401.5 ;

ts = 5e-5 ;

t = ts:ts:20 ; 
error = 0.1 * sin(2 * pi * freq * t) ;
freq_l = ones(size(error)) * freq ;

figure ;
plot(t, error) ;

data = [error', freq_l'] ;
dlmwrite('error_freq_for_test.txt', data) ;

 