--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.1
--  \   \         Application : sch2hdl
--  /   /         Filename : Section2_Schematic.vhf
-- /___/   /\     Timestamp : 04/10/2013 17:21:45
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family xc9500xl -flat -suppress -vhdl "Z:/Windows.Documents/My Documents/Sophomore/Section2/Section2_Schematic.vhf" -w "Z:/Windows.Documents/My Documents/Sophomore/Section2/Section2_Schematic.sch"
--Design Name: Section2_Schematic
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

entity Section2_Schematic is
   port ( A : in    std_logic; 
          B : in    std_logic; 
          C : in    std_logic; 
          Z : out   std_logic);
end Section2_Schematic;

architecture BEHAVIORAL of Section2_Schematic is
   attribute BOX_TYPE   : string ;
   signal XLXN_1  : std_logic;
   signal XLXN_2  : std_logic;
   signal XLXN_3  : std_logic;
   signal XLXN_4  : std_logic;
   signal XLXN_6  : std_logic;
   signal XLXN_7  : std_logic;
   signal XLXN_9  : std_logic;
   signal XLXN_10 : std_logic;
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
   component XOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR2 : component is "BLACK_BOX";
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
   component IBUF
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of IBUF : component is "BLACK_BOX";
   
begin
   XLXI_1 : AND2
      port map (I0=>XLXN_9,
                I1=>XLXN_10,
                O=>Z);
   
   XLXI_2 : OR2
      port map (I0=>XLXN_6,
                I1=>XLXN_4,
                O=>XLXN_9);
   
   XLXI_3 : XOR2
      port map (I0=>XLXN_4,
                I1=>XLXN_2,
                O=>XLXN_10);
   
   XLXI_4 : INV
      port map (I=>XLXN_3,
                O=>XLXN_4);
   
   XLXI_5 : INV
      port map (I=>XLXN_1,
                O=>XLXN_2);
   
   XLXI_6 : INV
      port map (I=>XLXN_7,
                O=>XLXN_6);
   
   XLXI_7 : IBUF
      port map (I=>A,
                O=>XLXN_1);
   
   XLXI_8 : IBUF
      port map (I=>B,
                O=>XLXN_3);
   
   XLXI_9 : IBUF
      port map (I=>C,
                O=>XLXN_7);
   
end BEHAVIORAL;


