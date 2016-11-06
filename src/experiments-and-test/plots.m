n=[1:10]*100*70;
%%
b1k1=[0.017 0.027 0.036 0.039 0.044 0.049 0.059 0.065 0.071 0.074];
b1k2=[0.017 0.027 0.030 0.035 0.044 0.053 0.069 0.064 0.067 0.077];
b1k5=[0.013 0.020 0.032 0.034 0.042 0.046 0.052 0.058 0.063 0.072]; 
%legend('k=1','k=2');
plot(n,b1k1)
hold on 
plot(n, b1k2)
hold on
plot(n,b1k5)
xlabel ('text size');
ylabel ('time');
legend('k=1','k=2', 'k=5');
title('sequential baseline 1');
%%
b2k1=[0.011 0.013 0.020 0.014 0.017 0.019 0.023 0.021 0.023 0.019];
b2k2=[0.011 0.014 0.016 0.017 0.016 0.026 0.018 0.024 0.026 0.023];
b2k5=[0.009 0.014 0.015 0.015 0.017 0.018 0.024 0.021 0.024 0.025];
figure
plot(n,b2k1)
hold on 
plot(n, b2k2)
hold on 
plot(n,b2k5)
xlabel ('text size');
ylabel ('time');
legend('k=1','k=2', 'k=5');
title('sequential baseline 2');
%%
effk1=[0.012 0.015 0.021 0.017 0.016 0.021 0.019 0.020 0.024 0.022];
effk2=[0.012 0.019 0.015 0.018 0.022 0.025 0.025 0.030 0.029 0.029];
effk5=[0.010 0.014 0.017 0.019 0.022 0.024 0.029 0.031 0.045 0.036];
figure
plot(n,effk1)
hold on 
plot(n, effk2)
hold on
plot(n, effk5)
xlabel ('text size');
ylabel ('time');
legend('k=1','k=2','k=5');
title('efficient sequential baseline');
%%
p1k1=[0.014 0.021 0.027 0.034 0.040 0.046 0.052 0.065 0.065 0.075];
p1k2=[0.014 0.021 0.030 0.034 0.043 0.047 0.058 0.059 0.064 0.073];
p1k5=[0.016 0.023 0.029 0.032 0.041 0.046 0.053 0.062 0.064 0.070]; 
figure
plot(n,p1k1)
hold on 
plot(n, p1k2)
hold on
plot(n,p1k5)
xlabel ('text size');
ylabel ('time');
legend('k=1','k=2', 'k=5');
title('parallel baseline 1');
%%
p2k1=[0.009 0.009 0.010 0.012 0.013 0.013 0.014 0.016 0.016 0.017];
p2k2=[0.008 0.010 0.010 0.012 0.014 0.014 0.016 0.018 0.020 0.020];
p2k5=[0.009 0.013 0.015 0.014 0.016 0.018 0.021 0.023 0.023 0.029];
figure
plot(n,p2k1)
hold on 
plot(n, p2k2)
hold on 
plot(n,p2k5)
xlabel ('text size');
ylabel ('time');
legend('k=1','k=2', 'k=5');
title('parallel baseline 2');
%%
figure 
plot (n,b1k5)
hold on 
plot(n,p1k5)
xlabel ('text size');
ylabel ('time');
legend('sequential 1','parallel 1');
title('comparison of sequential and parallel of baseline 1 for k=5');
%%
figure 
plot (n,b2k5)
hold on 
plot(n,p2k5)
xlabel ('text size');
ylabel ('time');
legend('sequential 2','parallel 2');
title('comparison of sequential and parallel of baseline 2 for k=5');
