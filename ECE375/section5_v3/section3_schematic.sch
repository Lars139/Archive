<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="Re" />
        <signal name="PINA" />
        <signal name="PINB" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="PINC" />
        <signal name="Ld" />
        <signal name="Rd" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_34" />
        <signal name="XLXN_35" />
        <signal name="Le" />
        <signal name="B" />
        <signal name="C" />
        <signal name="A" />
        <signal name="XLXN_37" />
        <signal name="XLXN_38" />
        <signal name="XLXN_39" />
        <signal name="XLXN_40" />
        <signal name="XLXN_41" />
        <signal name="XLXN_42" />
        <signal name="XLXN_43" />
        <signal name="XLXN_44" />
        <signal name="XLXN_45" />
        <signal name="XLXN_46" />
        <port polarity="Output" name="Re" />
        <port polarity="Output" name="Ld" />
        <port polarity="Output" name="Rd" />
        <port polarity="Output" name="Le" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="A" />
        <blockdef name="ibuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
        </blockdef>
        <blockdef name="and2b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="and3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
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
        <blockdef name="and3b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
        </blockdef>
        <blockdef name="and2b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
        </blockdef>
        <blockdef name="and3b3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="40" y1="-192" y2="-192" x1="0" />
            <circle r="12" cx="52" cy="-192" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
        </blockdef>
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
        <block symbolname="ibuf" name="XLXI_1">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="PINA" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_2">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="PINB" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_3">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="PINC" name="O" />
        </block>
        <block symbolname="and2b2" name="XLXI_8">
            <blockpin signalname="PINC" name="I0" />
            <blockpin signalname="PINB" name="I1" />
            <blockpin signalname="XLXN_8" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_9">
            <blockpin signalname="PINC" name="I0" />
            <blockpin signalname="PINB" name="I1" />
            <blockpin signalname="PINA" name="I2" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_10">
            <blockpin signalname="XLXN_9" name="I0" />
            <blockpin signalname="XLXN_8" name="I1" />
            <blockpin signalname="Re" name="O" />
        </block>
        <block symbolname="and3b2" name="XLXI_11">
            <blockpin signalname="PINB" name="I0" />
            <blockpin signalname="PINA" name="I1" />
            <blockpin signalname="PINC" name="I2" />
            <blockpin signalname="XLXN_26" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_12">
            <blockpin signalname="PINC" name="I0" />
            <blockpin signalname="PINA" name="I1" />
            <blockpin signalname="XLXN_27" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_13">
            <blockpin signalname="XLXN_27" name="I0" />
            <blockpin signalname="XLXN_26" name="I1" />
            <blockpin signalname="Ld" name="O" />
        </block>
        <block symbolname="and3b3" name="XLXI_14">
            <blockpin signalname="PINC" name="I0" />
            <blockpin signalname="PINB" name="I1" />
            <blockpin signalname="PINA" name="I2" />
            <blockpin signalname="XLXN_34" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_15">
            <blockpin signalname="PINC" name="I0" />
            <blockpin signalname="PINB" name="I1" />
            <blockpin signalname="XLXN_35" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_16">
            <blockpin signalname="XLXN_35" name="I0" />
            <blockpin signalname="XLXN_34" name="I1" />
            <blockpin signalname="Le" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_17">
            <blockpin signalname="PINC" name="I0" />
            <blockpin signalname="PINC" name="I1" />
            <blockpin signalname="Rd" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="Re">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2560" y="384" type="branch" />
            <wire x2="2048" y1="464" y2="464" x1="1792" />
            <wire x2="2048" y1="384" y2="464" x1="2048" />
            <wire x2="2560" y1="384" y2="384" x1="2048" />
            <wire x2="2704" y1="384" y2="384" x1="2560" />
        </branch>
        <branch name="PINB">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="592" y="224" type="branch" />
            <wire x2="592" y1="224" y2="224" x1="576" />
            <wire x2="768" y1="224" y2="224" x1="592" />
            <wire x2="768" y1="224" y2="352" x1="768" />
            <wire x2="1008" y1="352" y2="352" x1="768" />
            <wire x2="768" y1="352" y2="560" x1="768" />
            <wire x2="1008" y1="560" y2="560" x1="768" />
            <wire x2="768" y1="560" y2="928" x1="768" />
            <wire x2="1008" y1="928" y2="928" x1="768" />
            <wire x2="768" y1="928" y2="1328" x1="768" />
            <wire x2="1008" y1="1328" y2="1328" x1="768" />
            <wire x2="768" y1="1328" y2="1520" x1="768" />
            <wire x2="1008" y1="1520" y2="1520" x1="768" />
        </branch>
        <instance x="352" y="160" name="XLXI_1" orien="R0" />
        <instance x="352" y="256" name="XLXI_2" orien="R0" />
        <instance x="336" y="368" name="XLXI_3" orien="R0" />
        <instance x="1008" y="480" name="XLXI_8" orien="R0" />
        <instance x="1008" y="688" name="XLXI_9" orien="R0" />
        <instance x="1536" y="560" name="XLXI_10" orien="R0" />
        <branch name="XLXN_8">
            <wire x2="1392" y1="384" y2="384" x1="1264" />
            <wire x2="1392" y1="384" y2="432" x1="1392" />
            <wire x2="1536" y1="432" y2="432" x1="1392" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="1392" y1="560" y2="560" x1="1264" />
            <wire x2="1392" y1="496" y2="560" x1="1392" />
            <wire x2="1536" y1="496" y2="496" x1="1392" />
        </branch>
        <branch name="PINC">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="608" y="336" type="branch" />
            <wire x2="608" y1="336" y2="336" x1="560" />
            <wire x2="832" y1="336" y2="336" x1="608" />
            <wire x2="832" y1="336" y2="416" x1="832" />
            <wire x2="1008" y1="416" y2="416" x1="832" />
            <wire x2="832" y1="416" y2="624" x1="832" />
            <wire x2="1008" y1="624" y2="624" x1="832" />
            <wire x2="832" y1="624" y2="720" x1="832" />
            <wire x2="832" y1="720" y2="800" x1="832" />
            <wire x2="1008" y1="800" y2="800" x1="832" />
            <wire x2="832" y1="800" y2="1120" x1="832" />
            <wire x2="1008" y1="1120" y2="1120" x1="832" />
            <wire x2="832" y1="1120" y2="1392" x1="832" />
            <wire x2="1008" y1="1392" y2="1392" x1="832" />
            <wire x2="832" y1="1392" y2="1584" x1="832" />
            <wire x2="1008" y1="1584" y2="1584" x1="832" />
            <wire x2="2224" y1="720" y2="720" x1="832" />
            <wire x2="2288" y1="720" y2="720" x1="2224" />
            <wire x2="2304" y1="720" y2="720" x1="2288" />
            <wire x2="2304" y1="624" y2="624" x1="2224" />
            <wire x2="2224" y1="624" y2="720" x1="2224" />
            <wire x2="2304" y1="688" y2="688" x1="2288" />
            <wire x2="2288" y1="688" y2="720" x1="2288" />
        </branch>
        <branch name="Rd">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2608" y="720" type="branch" />
            <wire x2="2608" y1="720" y2="720" x1="2528" />
            <wire x2="2704" y1="720" y2="720" x1="2608" />
            <wire x2="2560" y1="720" y2="720" x1="2528" />
            <wire x2="2592" y1="720" y2="720" x1="2560" />
            <wire x2="2560" y1="720" y2="784" x1="2560" />
            <wire x2="2624" y1="784" y2="784" x1="2560" />
            <wire x2="2624" y1="656" y2="656" x1="2560" />
            <wire x2="2624" y1="656" y2="784" x1="2624" />
        </branch>
        <instance x="1008" y="992" name="XLXI_11" orien="R0" />
        <instance x="1008" y="1184" name="XLXI_12" orien="R0" />
        <branch name="PINA">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="608" y="128" type="branch" />
            <wire x2="608" y1="128" y2="128" x1="576" />
            <wire x2="688" y1="128" y2="128" x1="608" />
            <wire x2="688" y1="128" y2="496" x1="688" />
            <wire x2="1008" y1="496" y2="496" x1="688" />
            <wire x2="688" y1="496" y2="864" x1="688" />
            <wire x2="1008" y1="864" y2="864" x1="688" />
            <wire x2="688" y1="864" y2="1056" x1="688" />
            <wire x2="1008" y1="1056" y2="1056" x1="688" />
            <wire x2="688" y1="1056" y2="1264" x1="688" />
            <wire x2="1008" y1="1264" y2="1264" x1="688" />
        </branch>
        <instance x="1472" y="1088" name="XLXI_13" orien="R0" />
        <branch name="XLXN_26">
            <wire x2="1360" y1="864" y2="864" x1="1264" />
            <wire x2="1360" y1="864" y2="960" x1="1360" />
            <wire x2="1472" y1="960" y2="960" x1="1360" />
        </branch>
        <branch name="XLXN_27">
            <wire x2="1360" y1="1088" y2="1088" x1="1264" />
            <wire x2="1360" y1="1024" y2="1088" x1="1360" />
            <wire x2="1472" y1="1024" y2="1024" x1="1360" />
        </branch>
        <branch name="Ld">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2560" y="992" type="branch" />
            <wire x2="2560" y1="992" y2="992" x1="1728" />
            <wire x2="2736" y1="992" y2="992" x1="2560" />
        </branch>
        <instance x="1008" y="1456" name="XLXI_14" orien="R0" />
        <instance x="1008" y="1648" name="XLXI_15" orien="R0" />
        <instance x="1472" y="1536" name="XLXI_16" orien="R0" />
        <branch name="XLXN_34">
            <wire x2="1360" y1="1328" y2="1328" x1="1264" />
            <wire x2="1360" y1="1328" y2="1408" x1="1360" />
            <wire x2="1472" y1="1408" y2="1408" x1="1360" />
        </branch>
        <branch name="XLXN_35">
            <wire x2="1360" y1="1552" y2="1552" x1="1264" />
            <wire x2="1360" y1="1472" y2="1552" x1="1360" />
            <wire x2="1472" y1="1472" y2="1472" x1="1360" />
        </branch>
        <branch name="Le">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2576" y="1264" type="branch" />
            <wire x2="2000" y1="1440" y2="1440" x1="1728" />
            <wire x2="2000" y1="1264" y2="1440" x1="2000" />
            <wire x2="2576" y1="1264" y2="1264" x1="2000" />
            <wire x2="2736" y1="1264" y2="1264" x1="2576" />
        </branch>
        <branch name="B">
            <wire x2="352" y1="224" y2="224" x1="320" />
        </branch>
        <branch name="C">
            <wire x2="336" y1="336" y2="336" x1="304" />
        </branch>
        <branch name="A">
            <wire x2="352" y1="128" y2="128" x1="320" />
        </branch>
        <iomarker fontsize="28" x="320" y="128" name="A" orien="R180" />
        <iomarker fontsize="28" x="320" y="224" name="B" orien="R180" />
        <iomarker fontsize="28" x="304" y="336" name="C" orien="R180" />
        <iomarker fontsize="28" x="2704" y="384" name="Re" orien="R0" />
        <iomarker fontsize="28" x="2704" y="720" name="Rd" orien="R0" />
        <iomarker fontsize="28" x="2736" y="992" name="Ld" orien="R0" />
        <iomarker fontsize="28" x="2736" y="1264" name="Le" orien="R0" />
        <instance x="2304" y="752" name="XLXI_17" orien="R0" />
    </sheet>
</drawing>