clear

M = 28;

for i=0:999,
  omega(i+1) = pi * i / 999;
end;


for i=0:999,
  sum_t = 0;
  sum_b = 0;
  
  for k=1:M/2,
    % h får altid M/2 så det kan optimeres ud.
    h = ((sin((pi/4) * k)) / (pi * k));
    
    a = 2 * h;
    % Hamming:
    a = a * (0.54 - 0.46 * cos( 2 * pi * (k + (M/2)) / (M)));
    
    sum_t = sum_t + a * cos(k * omega(i+1));
    sum_b = sum_b + a;
  end;
  
  % Når k=0
  sum_t = sum_t + 0.25;
  sum_b = sum_b + 0.25;
  
  amp(i+1) = sum_t / sum_b;
  
end;

plot(omega, 20 * log10(abs(amp)), 3/16 * pi, -1, "+", 3/8 * pi, -10, "+")
grid;
xlabel("Frequency");
ylabel("Amplitude [dB]");