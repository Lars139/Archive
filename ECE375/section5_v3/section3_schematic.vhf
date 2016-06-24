--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.1
--  \   \         Application : sch2hdl
--  /   /         Filename : section3_schematic.vhf
-- /___/   /\     Timestamp : 05/09/2013 13:16:15
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family xc9500xl -flat -suppress -vhdl "Z:/Windows.Documents/My Documents/Sophomore/section5_v3/section3_schematic.vhf" -w "Z:/Windows.Documents/My Documents/Sophomore/section5_v3/section3_schematic.sch"
--Design Name: section3_schematic
--Device: xc9500xl
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesized and simulated, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity section3_schematic is
   port ( A  : in    std_logic; 
          B  : in    std_logic; 
          C  : in    std_logic; 
          Ld : out   std_logic; 
          Le : out   std_logic; 
          Rd : out   std_logic; 
          Re : out   std_logic);
end section3_schematic;

architecture BEHAVIORAL of section3_schematic is
   attribute BOX_TYPE   : string ;
   signal PINA    : std_logic;
   signal PINB    : std_logic;
   signal PINC    : std_logic;
   signal XLXN_8  : std_logic;
   signal XLXN_9  : std_logic;
   signal XLXN_26 : std_logic;
   signal XLXN_27 : std_logic;
   signal XLXN_34 : std_logic;
   signal XLXN_35 : std_logic;
   component IBUF
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of IBUF : component is "BLACK_BOX";
   
   component AND2B2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2B2 : component is "BLACK_BOX";
   
   component AND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3 : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
   component AND3B2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3B2 : component is "BLACK_BOX";
   
   component AND2B1
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2B1 : component is "BLACK_BOX";
   
   component AND3B3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3B3 : component is "BLACK_BOX";
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
begin
   XLXI_1 : IBUF
      port map (I=>A,
                O=>PINA);
   
   XLXI_2 : IBUF
      port map (I=>B,
                O=>PINB);
   
   XLXI_3 : IBUF
      port map (I=>C,
                O=>PINC);
   
   XLXI_8 : AND2B2
      port map (I0=>PINC,
                I1=>PINB,
                O=>XLXN_8);
   
   XLXI_9 : AND3
      port map (I0=>PINC,
                I1=>PINB,
                I2=>PINA,
                O=>XLXN_9);
   
   XLXI_10 : OR2
      port map (I0=>XLXN_9,
                I1=>XLXN_8,
                O=>Re);
   
   XLXI_11 : AND3B2
      port map (I0=>PINB,
                I1=>PINA,
                I2=>PINC,
                O=>XLXN_26);
   
   XLXI_12 : AND2B1
      port map (I0=>PINC,
                I1=>PINA,
                O=>XLXN_27);
   
   XLXI_13 : OR2
      port map (I0=>XLXN_27,
                I1=>XLXN_26,
                O=>Ld);
   
   XLXI_14 : AND3B3
      port map (I0=>PINC,
                I1=>PINB,
                I2=>PINA,
                O=>XLXN_34);
   
   XLXI_15 : AND2
      port map (I0=>PINC,
                I1=>PINB,
                O=>XLXN_35);
   
   XLXI_16 : OR2
      port map (I0=>XLXN_35,
                I1=>XLXN_34,
                O=>Le);
   
   XLXI_17 : AND2
      port map (I0=>PINC,
                I1=>PINC,
                O=>Rd);
   
end BEHAVIORAL;


