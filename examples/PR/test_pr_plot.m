close all;
clear ;
data = load('test_pr_output.txt') ;
figure()
plot(data(:, 1), data(:, 2)) ;
title('50Hz signal with resonance gain of 10')
