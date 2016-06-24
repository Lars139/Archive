.SUBCKT o_buffer_soic vin e_p4 e_vdd e_vss

***************************************************
*This buffer has trise and tfall times of < 1ns
*into a 75 ohm transmission line and capable of
*incident wave switching on lines as low as 25ohms.
*R. Traylor 12.12.08
*
* Includes L,R,C paracitics for the soic14 package.
*
* Also includes output ESD diodes   
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

*n-channel predrivers
M91  1 vin i_vss i_vss CMOSN W=20u  L=0.18u
M92  1 vin i_vss i_vss CMOSN W=10u  L=0.18u
M93  1 vin i_vss i_vss CMOSN W=5u   L=0.18u
M94  1 vin i_vss i_vss CMOSN W=2.5u L=0.18u

*p-channel predrivers
M95  1 vin i_vdd i_vdd CMOSP W=40u L=0.18u
M96  1 vin i_vdd i_vdd CMOSP W=20u L=0.18u
M97  1 vin i_vdd i_vdd CMOSP W=10u L=0.18u
M98  1 vin i_vdd i_vdd CMOSP W=5u  L=0.18u

*n-channel drivers
M3 vout 1 i_vss i_vss CMOSN W=800u  L=0.18u
M4 vout 1 i_vss i_vss CMOSN W=400u  L=0.18u
M5 vout 1 i_vss i_vss CMOSN W=200u  L=0.18u
M6 vout 1 i_vss i_vss CMOSN W=100u  L=0.18u

*p-channel drivers
M7  vout 1 i_vdd i_vdd CMOSP W=1600u L=0.18u
M8  vout 1 i_vdd i_vdd CMOSP W=800u  L=0.18u
M9  vout 1 i_vdd i_vdd CMOSP W=400u  L=0.18u
M10 vout 1 i_vdd i_vdd CMOSP W=200u  L=0.18u

*ESD diodes
*anode cathode
xESD1 i_vss vout   esd_diode
xESD2 vout  i_vdd  esd_diode

*package paracitics
*soic14, pin 14 vdd
cvdd  e_vdd    e_vss    6.2e-13
rvdd  i_vdd    tie_vdd  3.3e-2
lvdd  tie_vdd  e_vdd    3.8e-9

*soic14, pin 7 vss
cvss  i_vss    e_vss    6.2e-13
rvss  i_vss    tie_vss  3.4e-2
lvss  tie_vss  e_vss    3.9e-9

*uses values for pin 4 of soic14
cp4  e_p4    e_vss   3.6e-13   
rp4  vout    tie_p4  3.1e-2
lp4  tie_p4  e_p4    2.6e-9

.ENDS o_buffer_soic
