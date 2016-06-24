*ESD diode model "esd_diode.inc"
*created from two BAT17 schottky diodes in series

.SUBCKT esd_diode anode cathode 

*r1 models reverse mode of operation
r1 anode cathode  6E+07

*Two diodes in series to approximate Si diode operation
D1 anode tie      BAT17
D2 tie   cathode  BAT17
*
.MODEL BAT17 D 
+ IS = 1.419E-09 
+ N = 1.022 
+ BV = 6 
+ IBV = 2.45E-06 
+ RS = 5.112 
+ CJO = 7.867E-13 
+ VJ = 0.1043 
+ M = 0.1439 
+ FC = 0.5 
+ TT = 0 
+ EG = 0.69 
+ XTI = 2 
.ENDS
*
