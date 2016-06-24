function [r,m,peak] = crosscorr(x1,x2)
%do the cross-correlation
r = xcorr(x1,x2);
%finding the peak
[M, Idx] = max(r);
peak = Idx;
%returning value of m
m = r;
end