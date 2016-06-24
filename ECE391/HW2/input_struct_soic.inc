.SUBCKT input_struct_soic  vin pair_output e_vdd e_vss 

***************************************************
*This CMOS input stage is formed from mininum size
*transistors and ESD diodes. 
*R. Traylor 1.27.09
*
* Includes L,R,C paracitics for the soic4 package.
*
* Need to include output ESD structures and model
* input buffers.
*
* i_vdd refers to the internal (on die vdd)
* i_vss refers to the internal (on die vss)
* e_vdd refers to the external (vdd at package pin)
* e_vss refers to the external (vss at package pin)
*
***************************************************

.include npar0.18um.txt
.include ppar0.18um.txt
.include esd_diode.inc

*input transistors
*       drain      gate    source  bulk
M1  pair_output pair_input i_vss  i_vss  CMOSN  W=1.5u  L=0.18u
M2  pair_output pair_input i_vdd  i_vdd  CMOSP  W=3.0u  L=0.18u

*output load for input pair
c1  pair_output i_vss 10fF
r1  pair_output i_vss 1e7

*ESD diodes
*anode cathode
*xESD1 i_vss       pair_input  esd_diode
*xESD2 pair_input  i_vdd       esd_diode

*package paracitics
*soic14, pin 14 vdd
cvdd  e_vdd    e_vss     6.2e-13
rvdd  i_vdd    tie_vdd   3.3e-2
lvdd  tie_vdd  e_vdd     3.8e-9

*soic14, pin 7 vss
cvss  i_vss    e_vss     6.2e-13
rvss  e_vss    tie_vss   3.4e-2
lvss  tie_vss  i_vss     3.9e-9

*uses values for pin 4 of soic14
cp4  vin     e_vss       3.6e-13   
rp4  vin     tie_p4      3.1e-2
lp4  tie_p4  pair_input  2.6e-9

.ENDS input_struct_soic
