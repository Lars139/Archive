%vid = videoinput('winvideo',1,'YUY2_160x120');
%vid.ReturnedColorspace = 'rgb';

%preview(vid);

%pic = getsnapshot(vid);

%imwrite(pic, 'bear.bmp', 'BMP');

pic = imread('elliott1.bmp', 'BMP');  %for loaind the pic after saved
