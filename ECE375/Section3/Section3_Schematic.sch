<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_3" />
        <signal name="XLXN_4" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="XLXN_17" />
        <signal name="XLXN_20" />
        <signal name="XLXN_24" />
        <signal name="A" />
        <signal name="B" />
        <signal name="C" />
        <signal name="Le" />
        <signal name="Ld" />
        <signal name="Re" />
        <signal name="Rd" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Output" name="Le" />
        <port polarity="Output" name="Ld" />
        <port polarity="Output" name="Re" />
        <port polarity="Output" name="Rd" />
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
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
        <blockdef name="ibuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
        </blockdef>
        <block symbolname="and2" name="XLXI_2">
            <blockpin signalname="XLXN_12" name="I0" />
            <blockpin signalname="XLXN_11" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="XLXN_13" name="I0" />
            <blockpin signalname="XLXN_17" name="I1" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_6">
            <blockpin signalname="XLXN_15" name="I0" />
            <blockpin signalname="XLXN_14" name="I1" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_7">
            <blockpin signalname="XLXN_24" name="I0" />
            <blockpin signalname="XLXN_16" name="I1" />
            <blockpin signalname="XLXN_8" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_8">
            <blockpin signalname="XLXN_17" name="I" />
            <blockpin signalname="Ld" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_9">
            <blockpin signalname="XLXN_24" name="I" />
            <blockpin signalname="Rd" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_10">
            <blockpin signalname="XLXN_4" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="Le" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_11">
            <blockpin signalname="XLXN_8" name="I0" />
            <blockpin signalname="XLXN_7" name="I1" />
            <blockpin signalname="Re" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_15">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_17" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_16">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_20" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_17">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_24" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_22">
            <blockpin signalname="XLXN_20" name="I" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_23">
            <blockpin signalname="XLXN_24" name="I" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_24">
            <blockpin signalname="XLXN_20" name="I" />
            <blockpin signalname="XLXN_13" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_25">
            <blockpin signalname="XLXN_17" name="I" />
            <blockpin signalname="XLXN_14" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_26">
            <blockpin signalname="XLXN_20" name="I" />
            <blockpin signalname="XLXN_15" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_27">
            <blockpin signalname="XLXN_20" name="I" />
            <blockpin signalname="XLXN_16" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="2080" y="880" name="XLXI_2" orien="R0" />
        <instance x="2080" y="1056" name="XLXI_3" orien="R0" />
        <instance x="2080" y="1968" name="XLXI_6" orien="R0" />
        <instance x="2080" y="2128" name="XLXI_7" orien="R0" />
        <instance x="2080" y="1424" name="XLXI_8" orien="R0" />
        <instance x="2096" y="2432" name="XLXI_9" orien="R0" />
        <instance x="2592" y="960" name="XLXI_10" orien="R0" />
        <instance x="2576" y="2016" name="XLXI_11" orien="R0" />
        <instance x="256" y="288" name="XLXI_15" orien="R90" />
        <instance x="512" y="288" name="XLXI_16" orien="R90" />
        <instance x="752" y="304" name="XLXI_17" orien="R90" />
        <branch name="XLXN_3">
            <wire x2="2464" y1="784" y2="784" x1="2336" />
            <wire x2="2464" y1="784" y2="832" x1="2464" />
            <wire x2="2592" y1="832" y2="832" x1="2464" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="2464" y1="960" y2="960" x1="2336" />
            <wire x2="2464" y1="896" y2="960" x1="2464" />
            <wire x2="2592" y1="896" y2="896" x1="2464" />
        </branch>
        <branch name="XLXN_7">
            <wire x2="2448" y1="1872" y2="1872" x1="2336" />
            <wire x2="2448" y1="1872" y2="1888" x1="2448" />
            <wire x2="2576" y1="1888" y2="1888" x1="2448" />
        </branch>
        <branch name="XLXN_8">
            <wire x2="2448" y1="2032" y2="2032" x1="2336" />
            <wire x2="2448" y1="1952" y2="2032" x1="2448" />
            <wire x2="2576" y1="1952" y2="1952" x1="2448" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="2080" y1="752" y2="752" x1="2048" />
        </branch>
        <instance x="1824" y="784" name="XLXI_22" orien="R0" />
        <branch name="XLXN_12">
            <wire x2="2080" y1="816" y2="816" x1="2048" />
        </branch>
        <instance x="1824" y="848" name="XLXI_23" orien="R0" />
        <branch name="XLXN_13">
            <wire x2="2080" y1="992" y2="992" x1="2048" />
        </branch>
        <instance x="1824" y="1024" name="XLXI_24" orien="R0" />
        <branch name="XLXN_14">
            <wire x2="2080" y1="1840" y2="1840" x1="2048" />
        </branch>
        <instance x="1824" y="1872" name="XLXI_25" orien="R0" />
        <branch name="XLXN_15">
            <wire x2="2080" y1="1904" y2="1904" x1="2048" />
        </branch>
        <instance x="1824" y="1936" name="XLXI_26" orien="R0" />
        <branch name="XLXN_16">
            <wire x2="2080" y1="2000" y2="2000" x1="2048" />
        </branch>
        <instance x="1824" y="2032" name="XLXI_27" orien="R0" />
        <branch name="XLXN_17">
            <wire x2="288" y1="512" y2="928" x1="288" />
            <wire x2="2080" y1="928" y2="928" x1="288" />
            <wire x2="288" y1="928" y2="1392" x1="288" />
            <wire x2="2080" y1="1392" y2="1392" x1="288" />
            <wire x2="288" y1="1392" y2="1840" x1="288" />
            <wire x2="1824" y1="1840" y2="1840" x1="288" />
        </branch>
        <branch name="XLXN_20">
            <wire x2="544" y1="512" y2="752" x1="544" />
            <wire x2="1824" y1="752" y2="752" x1="544" />
            <wire x2="544" y1="752" y2="992" x1="544" />
            <wire x2="1824" y1="992" y2="992" x1="544" />
            <wire x2="544" y1="992" y2="1904" x1="544" />
            <wire x2="1824" y1="1904" y2="1904" x1="544" />
            <wire x2="544" y1="1904" y2="2000" x1="544" />
            <wire x2="1824" y1="2000" y2="2000" x1="544" />
        </branch>
        <branch name="XLXN_24">
            <wire x2="784" y1="528" y2="816" x1="784" />
            <wire x2="1824" y1="816" y2="816" x1="784" />
            <wire x2="784" y1="816" y2="2064" x1="784" />
            <wire x2="2080" y1="2064" y2="2064" x1="784" />
            <wire x2="784" y1="2064" y2="2400" x1="784" />
            <wire x2="2096" y1="2400" y2="2400" x1="784" />
        </branch>
        <branch name="A">
            <wire x2="288" y1="192" y2="288" x1="288" />
        </branch>
        <branch name="B">
            <wire x2="544" y1="192" y2="288" x1="544" />
        </branch>
        <branch name="C">
            <wire x2="784" y1="192" y2="304" x1="784" />
        </branch>
        <branch name="Le">
            <wire x2="3104" y1="864" y2="864" x1="2848" />
            <wire x2="3328" y1="864" y2="864" x1="3104" />
            <wire x2="3424" y1="864" y2="864" x1="3328" />
        </branch>
        <branch name="Ld">
            <wire x2="3104" y1="1392" y2="1392" x1="2304" />
            <wire x2="3104" y1="1392" y2="1408" x1="3104" />
            <wire x2="3328" y1="1408" y2="1408" x1="3104" />
            <wire x2="3424" y1="1392" y2="1392" x1="3328" />
            <wire x2="3328" y1="1392" y2="1408" x1="3328" />
        </branch>
        <branch name="Re">
            <wire x2="2960" y1="1920" y2="1920" x1="2832" />
            <wire x2="2960" y1="1904" y2="1920" x1="2960" />
            <wire x2="3088" y1="1904" y2="1904" x1="2960" />
            <wire x2="3312" y1="1904" y2="1904" x1="3088" />
            <wire x2="3392" y1="1904" y2="1904" x1="3312" />
            <wire x2="3392" y1="1888" y2="1904" x1="3392" />
        </branch>
        <branch name="Rd">
            <wire x2="2704" y1="2400" y2="2400" x1="2320" />
            <wire x2="2704" y1="2352" y2="2400" x1="2704" />
            <wire x2="3088" y1="2352" y2="2352" x1="2704" />
            <wire x2="3312" y1="2352" y2="2352" x1="3088" />
            <wire x2="3408" y1="2352" y2="2352" x1="3312" />
        </branch>
        <iomarker fontsize="28" x="784" y="192" name="C" orien="R270" />
        <iomarker fontsize="28" x="288" y="192" name="A" orien="R270" />
        <iomarker fontsize="28" x="544" y="192" name="B" orien="R270" />
        <iomarker fontsize="28" x="3392" y="1888" name="Re" orien="R270" />
        <iomarker fontsize="28" x="3408" y="2352" name="Rd" orien="R0" />
        <iomarker fontsize="28" x="3424" y="864" name="Le" orien="R0" />
        <iomarker fontsize="28" x="3424" y="1392" name="Ld" orien="R0" />
    </sheet>
</drawing>