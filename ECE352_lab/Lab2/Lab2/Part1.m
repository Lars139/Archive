%Author: Rattanai Sawaspnaich
%Co-Author: Elliott Highfile
%Oregon State University ECE 353

clear all
close all

%Change these var if you needed
Ds = 11/80; %inch per pixel  --- AKA 25 cycles on the page
k_max = 2;  %number of max to be found
css_num_max = 5; %The closest N-th element to WANTED will be chosen
WANTED = 2.25; %freq to be found


pic = imread('color_bars_2.bmp', 'BMP');  %for loaing the pic

r = pic(:,:,1);
g = pic(:,:,2);
b = pic(:,:,3);
%gpic = rgb2gray(r);

figure
imshow(r)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

curPix = 4; %cut out the white col at the top
cnt = 1;

while curPix < 57
    %turning pic into R/G/B scale
    R = fft(r(curPix,:));
    G = fft(g(curPix,:));
    B = fft(b(curPix,:));
    
    %ignoring the first peak b/c of the DC sig
    RR = abs(R(:,2:length(R)));
    GG = abs(G(:,2:length(G)));
    BB = abs(B(:,2:length(B)));
    k = linspace(0, (1/(2*Ds)) , length( r(1,:) ) -1 ); %k scale
    
    for j = 1:k_max  %look for the top K_MAX numbers of  max values (per row)
        [Mx, MxI] = max(RR); %for red
        %k(1,MxI)  %uncomment this go get the magnitute at the k value
        Max_val_r(j) = k(1,MxI);
        RR(MxI) = -Inf;
        
        [Mx, MxI] = max(GG); %for green
        Max_val_g(j) = k(1,MxI);
        GG(MxI) = -Inf;
        
        [Mx, MxI] = max(BB); %for green
        Max_val_b(j) = k(1,MxI);
        BB(MxI) = -Inf;
    end
    
    k_MAX(cnt,:,1) = Max_val_r(:);
    k_MAX(cnt,:,2) = Max_val_g(:);
    k_MAX(cnt,:,3) = Max_val_b(:);
    
    %Plotting all the graph in the world
    %FIXME: get rid of the non-sense graph
    %{
figure
stem(k, RR)
tlt = sprintf('Red row# %d',cnt);
title(tlt)
xlabel('k (cyc/in)')
figure
stem(k, BB)
tlt = sprintf('Blue row # %d',cnt);
title(tlt)
xlabel('k (cyc/in)')
figure
stem(k, GG)
tlt = sprintf('Green row # %d',cnt);
title(tlt)
xlabel('k (cyc/in)')
    %}
    
    %taking care of the counter stuff
    cnt = cnt +1;
    curPix = curPix +4;
end

%find the the closest value of k_MAX to WANTED
%FIXME: This algorithm assume the k_MAX only contain the highest peaks
s_k = size(k_MAX);
csr_row = 1;
for i = 1:s_k(3)
    for j = 1:s_k(1)
        [Mn, MnI] = min (abs(k_MAX(j,:,i) - WANTED))
        %Each row of Closest = [Min_rowNum | Min_colNum | Min_DimNum | Min_val ]
        Closer(csr_row,1) = j;
        Closer(csr_row,2) = MnI;
        Closer(csr_row,3) = i;
        Closer(csr_row,4) = Mn;
        csr_row = csr_row+1;
    end
end

k = linspace(0, (1/(2*Ds)) , length( r(1,:) ) -1 ); %k scale
for kcnt = 1:css_num_max
    [Mc, McI]= min(Closer(:,4));
    for i = 1:4
        Closest(kcnt,i) = Closer(McI,i);
    end
    Closer(McI,4) = Inf;
    
    %Plotting stuff
    if Closest(kcnt,3) == 1 %graping red
        r = pic(:,:,1);
        curPix = 4*Closest(kcnt,1);
        R = fft(r(curPix,:));
        RR = abs(R(:,2:length(R)));
        figure
        stem(k, RR)
        tlt = sprintf('Rank: %d \n Red row# %d',kcnt,Closest(kcnt,1));
        title(tlt)
    elseif Closest(kcnt,3) == 2 %graphing green
        g = pic(:,:,2);
        curPix = 4*Closest(kcnt,1);
        G = fft(g(curPix,:));
        GG = abs(G(:,2:length(R)));
        figure
        stem(k, GG)
        tlt = sprintf('Rank: %d \n Green row# %d',kcnt,Closest(kcnt,1));
        title(tlt)
    elseif Closest(kcnt,3) == 3 %graphing blue
        b = pic(:,:,3);
        curPix = 4*Closest(kcnt,1);
        B = fft(b(curPix,:));
        BB = abs(B(:,2:length(R)));
        figure
        stem(k, BB)
        tlt = sprintf('Rank: %d \n Green row# %d',kcnt,Closest(kcnt,1));
        title(tlt)
    end %end of plotting
end
disp('Closest: [ Min_rowNum | Min_colNum | Min_dimNum | Min_diff ]');
Closest

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


