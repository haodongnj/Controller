s = tf([1, 0], 1) ;

Kp = 15 ;
Kr = 2000 ;
wr = 50 * 2 * pi ;
wi = pi ;

G_PR = Kp + Kr * s / (s^2 + wr^2)
figure
bode(G_PR)

G_QPR = Kp + 2 * wi * Kr * s / (s^2 + 2 * wi * s +  wr^2)
figure
bode(G_QPR)