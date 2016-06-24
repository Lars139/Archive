function img_proc(filename)
img = imread(filename);
figure
imshow(img)
r = img(:,:,1);
g = img(:,:,2);
b = img(:,:,3);

null = zeros(size(img,1), size(img,2));

R = cat(3, r, null, null);
%figure, imshow(R)
G = cat(3, null, g, null);
%figure, imshow(G)
B = cat(3, null, null, b);
%figure, imshow(B)
Gr = rgb2gray(img);
Gr = cat(3, Gr, Gr, Gr);
%figure, imshow(Gr)


all = [R, G ; B, Gr];
figure
montage(all);


end 
