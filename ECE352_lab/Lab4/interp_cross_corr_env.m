function ryx_interp=interp_cross_corr_env(x,y,interp_factor,Ts)
% Article interpolated cross-correlation envelope computation
%  x  --  channel 1 signal
%  y  --  channel 2 signal
%  interp_factor  --  1 (no interp), 2, 4, 8, 16 (power of 2)
%  Ts  --  sample interval in seconds
%  ryx_interp  --  interpolated cross-correlation; spacing per index is Ts/interp_factor

[N1,col]=size(x);
if col ~= 1
    error('Signal x must be a column vector.')
end
[N2,col]=size(y);
if col ~= 1
    error('Signal y must be a column vector.')
end
if N1 ~= N2
    error('Signal x and y lengths must be the same.')
end
N=N1;
X=fft([x;zeros(N,1)]);
Y=fft([y;zeros(N,1)]);
Ryx=Y.*conj(X);
Ryx_interp=[Ryx(1);2*Ryx(2:N);Ryx(N+1);zeros(2*interp_factor*N-N-1,1)];
ryx_interp=abs(fftshift(ifft(Ryx_interp))*interp_factor*Ts);