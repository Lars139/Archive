% Use: [RGB] = getpic;
%
% Where RGB is a image Matrix of dimension 60x80x3
%
% This function requires the getRGB.dll file
% The image is also saved in bmp format as p60x80.bmp

function [RGB] = getpic

[R,G,B] = getRGB;
RGB = uint8(zeros(60,80,3));
RGB(:,:,1) = uint8(R);
RGB(:,:,2) = uint8(G);
RGB(:,:,3) = uint8(B);
