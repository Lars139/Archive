/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x2f00eba5 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "//stak.engr.oregonstate.edu/students/g/galec/Windows.Documents/My Documents/Sophomore/Section_6/section_6_source.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {3U, 0U};
static unsigned int ng3[] = {1U, 0U};
static unsigned int ng4[] = {2U, 0U};
static unsigned int ng5[] = {4U, 0U};



static void Always_92_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;

LAB0:    t1 = (t0 + 2212U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(92, ng0);
    t2 = (t0 + 2696);
    *((int *)t2) = 1;
    t3 = (t0 + 2240);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(93, ng0);
    t4 = (t0 + 1092U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB5;

LAB6:    xsi_set_current_line(94, ng0);
    t2 = (t0 + 1688);
    t3 = (t2 + 36U);
    t4 = *((char **)t3);
    t5 = (t0 + 1596);
    xsi_vlogvar_wait_assign_value(t5, t4, 0, 0, 3, 0LL);

LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(93, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 1596);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 3, 0LL);
    goto LAB7;

}

static void Always_97_1(char *t0)
{
    char t9[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    int t8;
    char *t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    char *t17;
    char *t18;
    char *t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    char *t34;
    char *t35;

LAB0:    t1 = (t0 + 2356U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(97, ng0);
    t2 = (t0 + 2704);
    *((int *)t2) = 1;
    t3 = (t0 + 2384);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(98, ng0);
    t4 = (t0 + 1596);
    t5 = (t4 + 36U);
    t6 = *((char **)t5);

LAB5:    t7 = ((char*)((ng1)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t7, 3);
    if (t8 == 1)
        goto LAB6;

LAB7:    t2 = ((char*)((ng3)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB8;

LAB9:    t2 = ((char*)((ng4)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB10;

LAB11:    t2 = ((char*)((ng2)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB12;

LAB13:    t2 = ((char*)((ng5)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB14;

LAB15:
LAB16:    goto LAB2;

LAB6:    xsi_set_current_line(99, ng0);
    t10 = (t0 + 1184U);
    t11 = *((char **)t10);
    memset(t9, 0, 8);
    t10 = (t11 + 4);
    t12 = *((unsigned int *)t10);
    t13 = (~(t12));
    t14 = *((unsigned int *)t11);
    t15 = (t14 & t13);
    t16 = (t15 & 1U);
    if (t16 != 0)
        goto LAB20;

LAB18:    if (*((unsigned int *)t10) == 0)
        goto LAB17;

LAB19:    t17 = (t9 + 4);
    *((unsigned int *)t9) = 1;
    *((unsigned int *)t17) = 1;

LAB20:    t18 = (t9 + 4);
    t19 = (t11 + 4);
    t20 = *((unsigned int *)t11);
    t21 = (~(t20));
    *((unsigned int *)t9) = t21;
    *((unsigned int *)t18) = 0;
    if (*((unsigned int *)t19) != 0)
        goto LAB22;

LAB21:    t26 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t26 & 1U);
    t27 = *((unsigned int *)t18);
    *((unsigned int *)t18) = (t27 & 1U);
    t28 = (t9 + 4);
    t29 = *((unsigned int *)t28);
    t30 = (~(t29));
    t31 = *((unsigned int *)t9);
    t32 = (t31 & t30);
    t33 = (t32 != 0);
    if (t33 > 0)
        goto LAB23;

LAB24:    xsi_set_current_line(100, ng0);
    t2 = (t0 + 1276U);
    t3 = *((char **)t2);
    memset(t9, 0, 8);
    t2 = (t3 + 4);
    t12 = *((unsigned int *)t2);
    t13 = (~(t12));
    t14 = *((unsigned int *)t3);
    t15 = (t14 & t13);
    t16 = (t15 & 1U);
    if (t16 != 0)
        goto LAB29;

LAB27:    if (*((unsigned int *)t2) == 0)
        goto LAB26;

LAB28:    t4 = (t9 + 4);
    *((unsigned int *)t9) = 1;
    *((unsigned int *)t4) = 1;

LAB29:    t5 = (t9 + 4);
    t7 = (t3 + 4);
    t20 = *((unsigned int *)t3);
    t21 = (~(t20));
    *((unsigned int *)t9) = t21;
    *((unsigned int *)t5) = 0;
    if (*((unsigned int *)t7) != 0)
        goto LAB31;

LAB30:    t26 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t26 & 1U);
    t27 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t27 & 1U);
    t10 = (t9 + 4);
    t29 = *((unsigned int *)t10);
    t30 = (~(t29));
    t31 = *((unsigned int *)t9);
    t32 = (t31 & t30);
    t33 = (t32 != 0);
    if (t33 > 0)
        goto LAB32;

LAB33:    xsi_set_current_line(101, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1688);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 3);

LAB34:
LAB25:    goto LAB16;

LAB8:    xsi_set_current_line(102, ng0);
    t3 = ((char*)((ng4)));
    t4 = (t0 + 1688);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB16;

LAB10:    xsi_set_current_line(103, ng0);
    t3 = ((char*)((ng1)));
    t4 = (t0 + 1688);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB16;

LAB12:    xsi_set_current_line(104, ng0);
    t3 = ((char*)((ng5)));
    t4 = (t0 + 1688);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB16;

LAB14:    xsi_set_current_line(105, ng0);
    t3 = ((char*)((ng1)));
    t4 = (t0 + 1688);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB16;

LAB17:    *((unsigned int *)t9) = 1;
    goto LAB20;

LAB22:    t22 = *((unsigned int *)t9);
    t23 = *((unsigned int *)t19);
    *((unsigned int *)t9) = (t22 | t23);
    t24 = *((unsigned int *)t18);
    t25 = *((unsigned int *)t19);
    *((unsigned int *)t18) = (t24 | t25);
    goto LAB21;

LAB23:    xsi_set_current_line(99, ng0);
    t34 = ((char*)((ng2)));
    t35 = (t0 + 1688);
    xsi_vlogvar_assign_value(t35, t34, 0, 0, 3);
    goto LAB25;

LAB26:    *((unsigned int *)t9) = 1;
    goto LAB29;

LAB31:    t22 = *((unsigned int *)t9);
    t23 = *((unsigned int *)t7);
    *((unsigned int *)t9) = (t22 | t23);
    t24 = *((unsigned int *)t5);
    t25 = *((unsigned int *)t7);
    *((unsigned int *)t5) = (t24 | t25);
    goto LAB30;

LAB32:    xsi_set_current_line(100, ng0);
    t11 = ((char*)((ng3)));
    t17 = (t0 + 1688);
    xsi_vlogvar_assign_value(t17, t11, 0, 0, 3);
    goto LAB34;

}

static void Cont_109_2(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 2500U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(109, ng0);
    t2 = (t0 + 1596);
    t3 = (t2 + 36U);
    t4 = *((char **)t3);
    t5 = (t0 + 2756);
    t6 = (t5 + 32U);
    t7 = *((char **)t6);
    t8 = (t7 + 40U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 7U;
    t11 = t10;
    t12 = (t4 + 4);
    t13 = *((unsigned int *)t4);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t5, 0, 2);
    t18 = (t0 + 2712);
    *((int *)t18) = 1;

LAB1:    return;
}


extern void work_m_00000000002499265315_3756266784_init()
{
	static char *pe[] = {(void *)Always_92_0,(void *)Always_97_1,(void *)Cont_109_2};
	xsi_register_didat("work_m_00000000002499265315_3756266784", "isim/Section6_test_isim_beh.exe.sim/work/m_00000000002499265315_3756266784.didat");
	xsi_register_executes(pe);
}
