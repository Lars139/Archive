clear all
close all

Y = [1 2 ; 3 4];
H = [5 6 ; 7 8];

%  / Matrix right division  B/A == B*inv(A)
%  \ Matrix left division   A\B == inv(A)*B

x1 = eye(2)/Y
inv(Y)  % do the same as line above
toeplitz(x1);
x2 = eye(2)/H;
inv(H);

