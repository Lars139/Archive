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

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    uni9000_ver_m_00000000003510477262_2316096324_init();
    uni9000_ver_m_00000000000236260522_2449448540_init();
    uni9000_ver_m_00000000002123152668_0970595058_init();
    uni9000_ver_m_00000000003266096158_1108579578_init();
    work_m_00000000001772401288_1499369199_init();
    work_m_00000000003677433195_0451708241_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000003677433195_0451708241");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
