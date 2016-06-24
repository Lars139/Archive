<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="XLXN_4" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="A" />
        <signal name="B" />
        <signal name="C" />
        <signal name="Z" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Output" name="Z" />
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="or2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
        </blockdef>
        <blockdef name="xor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="60" y1="-128" y2="-128" x1="0" />
            <line x2="208" y1="-96" y2="-96" x1="256" />
            <arc ex="44" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <arc ex="64" ey="-144" sx="64" sy="-48" r="56" cx="32" cy="-96" />
            <line x2="64" y1="-144" y2="-144" x1="128" />
            <line x2="64" y1="-48" y2="-48" x1="128" />
            <arc ex="128" ey="-144" sx="208" sy="-96" r="88" cx="132" cy="-56" />
            <arc ex="208" ey="-96" sx="128" sy="-48" r="88" cx="132" cy="-136" />
        </blockdef>
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <blockdef name="ibuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
        </blockdef>
        <block symbolname="and2" name="XLXI_1">
            <blockpin signalname="XLXN_9" name="I0" />
            <blockpin signalname="XLXN_10" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_2">
            <blockpin signalname="XLXN_6" name="I0" />
            <blockpin signalname="XLXN_4" name="I1" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
        <block symbolname="xor2" name="XLXI_3">
            <blockpin signalname="XLXN_4" name="I0" />
            <blockpin signalname="XLXN_2" name="I1" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_4">
            <blockpin signalname="XLXN_3" name="I" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_5">
            <blockpin signalname="XLXN_1" name="I" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_6">
            <blockpin signalname="XLXN_7" name="I" />
            <blockpin signalname="XLXN_6" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_7">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_8">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_9">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1808" y="880" name="XLXI_1" orien="R0" />
        <instance x="1520" y="1104" name="XLXI_2" orien="R0" />
        <instance x="1488" y="656" name="XLXI_3" orien="R0" />
        <instance x="1136" y="848" name="XLXI_4" orien="R0" />
        <instance x="1152" y="480" name="XLXI_5" orien="R0" />
        <instance x="1152" y="1200" name="XLXI_6" orien="R0" />
        <instance x="880" y="496" name="XLXI_7" orien="R0" />
        <instance x="864" y="848" name="XLXI_8" orien="R0" />
        <instance x="896" y="1216" name="XLXI_9" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1120" y1="464" y2="464" x1="1104" />
            <wire x2="1120" y1="448" y2="464" x1="1120" />
            <wire x2="1152" y1="448" y2="448" x1="1120" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1424" y1="448" y2="448" x1="1376" />
            <wire x2="1424" y1="448" y2="528" x1="1424" />
            <wire x2="1488" y1="528" y2="528" x1="1424" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1136" y1="816" y2="816" x1="1088" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1424" y1="816" y2="816" x1="1360" />
            <wire x2="1424" y1="816" y2="976" x1="1424" />
            <wire x2="1520" y1="976" y2="976" x1="1424" />
            <wire x2="1424" y1="592" y2="816" x1="1424" />
            <wire x2="1488" y1="592" y2="592" x1="1424" />
        </branch>
        <branch name="XLXN_6">
            <wire x2="1440" y1="1168" y2="1168" x1="1376" />
            <wire x2="1440" y1="1040" y2="1168" x1="1440" />
            <wire x2="1520" y1="1040" y2="1040" x1="1440" />
        </branch>
        <branch name="XLXN_7">
            <wire x2="1136" y1="1184" y2="1184" x1="1120" />
            <wire x2="1136" y1="1168" y2="1184" x1="1136" />
            <wire x2="1152" y1="1168" y2="1168" x1="1136" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="1728" y1="816" y2="896" x1="1728" />
            <wire x2="1840" y1="896" y2="896" x1="1728" />
            <wire x2="1840" y1="896" y2="1008" x1="1840" />
            <wire x2="1808" y1="816" y2="816" x1="1728" />
            <wire x2="1840" y1="1008" y2="1008" x1="1776" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="1776" y1="560" y2="560" x1="1744" />
            <wire x2="1776" y1="560" y2="752" x1="1776" />
            <wire x2="1808" y1="752" y2="752" x1="1776" />
        </branch>
        <branch name="A">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="752" y="464" type="branch" />
            <wire x2="752" y1="464" y2="464" x1="704" />
            <wire x2="880" y1="464" y2="464" x1="752" />
        </branch>
        <branch name="B">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="768" y="816" type="branch" />
            <wire x2="768" y1="816" y2="816" x1="704" />
            <wire x2="864" y1="816" y2="816" x1="768" />
        </branch>
        <branch name="C">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="768" y="1184" type="branch" />
            <wire x2="768" y1="1184" y2="1184" x1="688" />
            <wire x2="896" y1="1184" y2="1184" x1="768" />
        </branch>
        <branch name="Z">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2192" y="784" type="branch" />
            <wire x2="2192" y1="784" y2="784" x1="2064" />
            <wire x2="2256" y1="784" y2="784" x1="2192" />
        </branch>
        <iomarker fontsize="28" x="704" y="464" name="A" orien="R180" />
        <iomarker fontsize="28" x="704" y="816" name="B" orien="R180" />
        <iomarker fontsize="28" x="688" y="1184" name="C" orien="R180" />
        <iomarker fontsize="28" x="2256" y="784" name="Z" orien="R0" />
    </sheet>
</drawing>