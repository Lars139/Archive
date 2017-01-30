Diode I-V Sweep

** This is a template to get you started in the right direction
** It won't necessarily have everything you need to extract your 
** I-V cureves but should get you going.

.options post node ingold=1 runlvl=0 relv=0.001 reli=0.001 DCAP=1

* FILL IN THE PARAMETERS below to match the values you calculated 
.MODEL diode1 D (IS=7.5204e-20 CJO=2.5115e-16 VJ=0.71564 

* LEAVE THESE PARAMETERS ALONE
                 +level=1 M=0.5 N=1.2 RS=1e-3)

* This part defines your spice circuit
Vsrc 0 1 DC 1
D1 0 1 diode1

* This defines your voltage or current sweeps
.DC Vsrc -1.5 1.5 0.01
.PRINT dc

* 516 students: don't forget your transient analysis!

.end
