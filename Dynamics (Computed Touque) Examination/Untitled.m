G = tf(1, conv([1 3], [1 8 20]))
Gk = feedback(165*G, 1)
step(Gk, 5)
grid on