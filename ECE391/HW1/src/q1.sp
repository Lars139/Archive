Simple T-line

*PULSE source parameters
*            initial   pulse   delay  trise  tfall  pulse  period
*             value    value                        width
*     PULSE(    0       1.0    2e-9    10p    10p   20e-9  80e-9)

*1.0v square wave source; 1ns delay, 100pS edges, 20ns pulse width, 40ns cycle time
Vin vin 0 1.0 PULSE(0 1.0 1e-9 100p 100p 20e-9 80e-9)

*source output impedance
rsrc vin tline_input 80

*transmission line, 50 ohm, 2ns electrical length
t1 tline_input 0 tline_output 0 z0=50 td=2ns

*termaination at end of T-line
rload tline_output 0 20 

.control
  set hcopydevtype=postscript

* color0 is background color
* color1 is the grid and text color
* colors 2-15 are for the vectors if you want to specify them
* uncomment next three lines to plot colors on white background
  set hcopypscolor=true
  set color0=rgb:f/f/f
  set color1=rgb:0/0/0

* to print the results directly to a printer uncomment the following line
* set hcopydev=kec3112

* run DC operating point simulation first
  op

*run transient simulation for 20ns with timesteps of 100ps
  tran 100ps 20ns

*plot nodes tline_input and tline_output every 1ns for 20ns
  plot  V(tline_input) V(tline_output) xl 1ns 20ns

*plot to .ps file nodes tline_input and tline_output every 1ns for 45ns
  hardcopy q1.ps V(tline_input) V(tline_output) xl 0.1ns 20ns

.endc

.end
