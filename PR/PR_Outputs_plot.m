close all 
clear ;
data = load('PR_Outputs.txt') ;
figure()
plot(data(:, 1), data(:, 2)) ;

