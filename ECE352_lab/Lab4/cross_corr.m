

function [r, m, m_peak] = cross_corr(x1, x2)
    x1 = flipud(x1);       %flipping channel 1
    r = conv(x1, x2);      %convolving with channel 2 (cross correlation)
    [~, m_peak] = max(abs(r));  %grabbing index for max delay...
                                ...(i.e.: m/(sampling rate) = lag)
    N = length(x1);             %number of samples
    m_peak = m_peak - N;        %adjustment for deltaT calculations
    m = linspace(-(N-1), (N-1), (2*N-1)); %delay for each sample...
                                          ...(i.e: used to plot against)
end