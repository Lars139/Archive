#include<stdio.h>

#include<limits.h>


#include<math.h>

int main()

{


unsigned short us_l, us_h; short s_l, s_h;

unsigned int ui_l, ui_h;  int i_l, i_h;

unsigned long ul_l, ul_h; long l_l, l_h;


int n;
printf("____________________________________________________________________\n\n");

printf("  Program: Largest_int.c\n");
printf("  Author: Rattanai Sawaspanich \n");

printf("  Date: 09/28/2012\n");

printf("  Description: Aren't they a little bit too many variables? \n");

printf("____________________________________________________________________\n");

s_l = SHRT_MIN; s_h = SHRT_MAX; us_h = USHRT_MAX; us_l = 0;


i_l = INT_MIN; i_h = INT_MAX; ui_h = UINT_MAX; ui_l = 0;

l_l = LONG_MIN; l_h = LONG_MAX; ul_h = ULONG_MAX; ul_l = 0;


for(n=0;n<2;n++)
{


printf("\n                                 SHORT\n");

printf("base:                   10 //             8 //                 16\n");

printf("signed min            %d // %o // %x\n",s_l,s_l,s_l);

printf("signed max            %d // %o // %x\n",s_h,s_h,s_h);

printf("unsigned min            %d // %o // %x\n",us_l,us_l,us_l);

printf("unsigned max          %d //  %o // %x\n",us_h,us_h,us_h);

printf("____________________________________________________________________\n\n");


printf("\n                               INTEGER\n");

printf("base:                   10 //                  8 //              16\n");

printf("signed min            %d // %o // %x\n",i_l,i_l,i_l);

printf("signed max            %d // %o // %x\n",i_h,i_h,i_h);

printf("unsigned min            %u // %o // %x\n",ui_l,ui_l,ui_l);

printf("unsigned max          %u // %o // %x\n",ui_h,ui_h,ui_h);

printf("____________________________________________________________________\n\n");

printf("\n                                 LONG\n");

printf("base:                   10 //              8 //              16\n");

printf("signed min              %ld // %lo // %lx\n",l_l,l_l,l_l);

printf("signed max              %ld //  %lo // %lx\n",l_h,l_h,l_h);

printf("unsigned min            %lu // %lo // %lx\n",ul_l,ul_l,ul_l);

printf("unsigned max            %lu // %lo // %lx\n",ul_h,ul_h,ul_h);

printf("____________________________________________________________________\n\n");


if(n==0)
printf("***********************ADD MAX, SUBTRACT MIN***************************\n\n");

us_l = us_l-1;
s_l = s_l-1;
ui_l = ui_l-1;
i_l = i_l-1;
ul_l = ul_l-1;
l_l = l_l-1;

us_h = us_h+1;
s_h = s_h+1;
ui_h = ui_h+1;
i_h = i_h+1;
ul_h = ul_h+1;
l_h = l_h+1;
}




printf("____________________________________________________________________\n");
printf("\n                   Largest \\ Smallest Number\n");
printf("____________________________________________________________________\n");
printf("base:                   SHORT //       INT //  LONG\n");

printf("signed min              %ld // %ld // %ld\n",((long) (((-1)*pow(2, sizeof(short)*8))-1)),((long) (((-1)*pow(2, sizeof(int)*8))-1)),(((unsigned long) (-1))/2)*(-1)-1);

printf("signed max              %d //  %ld // %ld \n",((long) ((pow(2, sizeof(short)*8)))),((long) (pow(2, sizeof(int)*8))),(((unsigned long) (-1))/2)-1);

printf("unsigned min            %ld // %ld // %ld \n",0, 0,0);

printf("unsigned max            %ld // %ld // %lu \n",((unsigned short) (-1)),((unsigned int) (-1)), ((unsigned long) ((pow(2, sizeof(long)*8-1)-1)*2+1)));

printf("____________________________________________________________________\n\n");


//((long) (((-1)*pow(2, sizeof(short)*8))-1))
//((unsigned long) (-1))













}
