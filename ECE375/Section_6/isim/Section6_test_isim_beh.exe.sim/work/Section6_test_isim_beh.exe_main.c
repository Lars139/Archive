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
    work_m_00000000000968354168_0306821083_init();
    work_m_00000000000652185338_2531671071_init();
    work_m_00000000002499265315_3756266784_init();
    work_m_00000000003588335453_3069169239_init();
    work_m_00000000001670356234_2275732874_init();
    work_m_00000000002060989362_3335543528_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000002060989362_3335543528");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
