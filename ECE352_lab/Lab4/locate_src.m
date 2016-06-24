

%triangulation formulas

function [dis_A, dis_B] = locate_src(A, B, s)
    if A > B
        A = A - 180;
    elseif B < A
        B = B - 180;
    elseif B == A
        return;
    end
    C = 180 - A - B;
    dis_A = s*sind(A)/sind(C);
    dis_B = s*sind(B)/sind(C);
end