%incident_angle.m
%evaluates the incident angle for either case

%case 1: Channel 1 leads Channel 2
%**see pre_lab drawing in lab instructions**
%delta_t is in seconds
%theta is in degrees
%d is the distance from left_mic to right_mic

function theta = incident_angle(m_peak, Fs, d)
    c = 300;    %speed of sound in meters/sec
    delta_t = m_peak/Fs;
    if delta_t > 0
        theta = acosd(c*delta_t/d);   
    else
        theta = acosd(-c*delta_t/d);
    end
end
