clear all
close all

%loading the original image
load('blur_data.mat');

%show image in gray scale
imagesc(blur_photo);
colormap(photo_gray_map);
tlt = sprintf('Blurred');
title(tlt)
n = size(blur_photo, 1);
 
%This goes w/ the reviewing the secret
p1 = figure;
colormap(p1,photo_gray_map);

for L=1:300; %ForLoop can go here
    
    %generating the inv mtx
    c=zeros(1,n);
    c(1) = 1/L;
    r = zeros(1,n);
    r(1:1:L)=1/L;
    H = toeplitz(c,r);
    
    %deblur the photo by dividing the blurred w/ inv mtx
    deblur_photo = blur_photo/H;
    
    %displaying the deblur photo
    imagesc(deblur_photo);
    
    %Double deblur  - Uncomment this path to review the secret
    PSF = fspecial('unsharp',0.5 );  %Set up PSF AKA filter
    filt = filter2(PSF, deblur_photo)/450; %Filtering
    imshow(filt);
    tlt = sprintf('L = %d',L);
    title(tlt)
    pause
    
end
