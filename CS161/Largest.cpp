#include<iostream>

#include<climits>


#include<cmath>

int main()

{


unsigned short us_l, us_h; 
short s_l, s_h;

unsigned int ui_l, ui_h;  
int i_l, i_h;

unsigned long ul_l, ul_h; 
long l_l, l_h;


int n;
std::cout<<"____________________________________________________________________\n\n";

std::cout<<"  Program: Largest_int.c\n";

std::cout<<"  Author: Rattanai Sawaspanich \n";

std::cout<<"  Date: 09/28/2012\n";

std::cout<<"  Description: Aren't they a little bit too many variables? \n";

std::cout<<"____________________________________________________________________\n";

s_l = SHRT_MIN; s_h = SHRT_MAX; us_h = USHRT_MAX; us_l = 0;


i_l = INT_MIN; i_h = INT_MAX; ui_h = UINT_MAX; ui_l = 0;

l_l = LONG_MIN; l_h = LONG_MAX; ul_h = ULONG_MAX; ul_l = 0;


for(n=0;n<2;n++)
{


std::cout<<"\n                                 SHORT\n";

std::cout<<"base:                   10 //             8 //                 16\n";

std::cout<<"signed min            "<<std::dec<<s_l<<"  //  "<<std::oct<<s_l<<"  //  "<<std::hex<<s_l<<"\n"; 

std::cout<<"signed max            "<<std::dec<<s_h<<"  //  "<<std::oct<<s_h<<"  //  "<<std::hex<<s_h<<"\n";
std::cout<<"unsigned min          "<<std::dec<<us_l<<"  //  "<<std::oct<<us_l<<"  //  "<<std::hex<<us_l<<"\n"; 
std::cout<<"unsigned max          "<<std::dec<<us_h<<"  //  "<<std::oct<<us_h<<"  //  "<<std::hex<<us_h<<"\n"; 
std::cout<<"____________________________________________________________________\n\n";


std::cout<<"\n                               INTEGER\n";

std::cout<<"base:                   10 //                  8 //              16\n";

std::cout<<"signed min            "<<std::dec<<i_l<<"  //  "<<std::oct<<i_l<<"  //  "<<std::hex<<i_l<<"\n"; 
std::cout<<"signed max            "<<std::dec<<i_h<<"  //  "<<std::oct<<i_h<<"  //  "<<std::hex<<i_h<<"\n";

std::cout<<"unsigned min          "<<std::dec<<ui_l<<"  //  "<<std::oct<<ui_l<<"  //  "<<std::hex<<ui_l<<"\n";

std::cout<<"unsigned max          "<<std::dec<<ui_h<<"  //  "<<std::oct<<ui_h<<"  //  "<<std::hex<<ui_h<<"\n";
std::cout<<"____________________________________________________________________\n\n";

std::cout<<"\n                                 LONG\n";

std::cout<<"base:                   10 //              8 //              16\n";

std::cout<<"signed min              "<<std::dec<<l_l<<"  //  "<<std::oct<<l_l<<"  //  "<<std::hex<<l_l<<"\n";

std::cout<<"signed max              "<<std::dec<<l_h<<"  //  "<<std::oct<<l_h<<"  //  "<<std::hex<<l_h<<"\n";

std::cout<<"unsigned min            "<<std::dec<<ul_l<<"  //  "<<std::oct<<ul_l<<"  //  "<<std::hex<<ul_l<<"\n";

std::cout<<"unsigned max            "<<std::dec<<ul_h<<"  //  "<<std::oct<<ul_h<<"  //  "<<std::hex<<ul_h<<"\n";


std::cout<<"____________________________________________________________________\n\n";


if(n==0)
std::cout<<"***********************ADD MAX, SUBTRACT MIN***************************\n\n";

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




std::cout<<"____________________________________________________________________\n";
std::cout<<"\n                   Largest \\ Smallest Number\n";
std::cout<<"____________________________________________________________________\n";
std::cout<<"base:                   SHORT //       INT //  LONG\n";

std::cout<<"signed min              "<<std::dec<<((long) (((-1)*pow(2, sizeof(short)*8-1))-1))<<"  //  "<<((long) (((-1)*pow(2, sizeof(int)*8-1))-1))<<"  //  -"<<(((unsigned long) (-1))/2)*(-1)-1<<"\n";

std::cout<<"signed max              "<<((long) ((pow(2, sizeof(short)*8-1))))<<"  //  "<<((long) (pow(2, sizeof(int)*8-1)))<<"  //  "<<(((unsigned long) (-1))/2)<<"\n";

std::cout<<"unsigned min               0//          0 //    0\n";

std::cout<<"unsigned max            "<<((unsigned short) (-1))<<"  //  "<<((unsigned int) (-1))<<"  //  "<<((unsigned long) ((pow(2, sizeof(long)*8-1)-1)*2+1))<<"\n";

std::cout<<"____________________________________________________________________\n\n";


//((long) (((-1)*pow(2, sizeof(short)*8))-1))
//((unsigned long) (-1))













}
