#include<iostream>
#include<cmath>

/*
 *Pragram Filename: integration
 *Author: Rattanai Sawaspanich
 *Date: 10/19/2012
 *Description: Use to approximate the value of area under the curve of x^4+3
 *Input: Starting and Ending point for the area, 
 *       Methode of area calculation
 *       Number of rectangles and/or trapezoids to use
 *
 *
 *Output: The evaluated function, Starting and ending point of the integral
 *Number of rectangles and/or trapezoids used
 * The area calculated by the method(s)
 *
 */


int main()
{
float a,b,i,j,ai,bi;
char re;
int nR, nT,m;
float Rec(float a, float b, int nR);
float Trap(float i, float j, int nT);
start:

std::cout<<"\nMethode of calculation (number only): 1.Rectangle 2.Trapezoid 3.Both"<<std::endl;
std::cin>>m;

std::cout<<"\nFunction: x^4+3\n""Start point: "<<std::endl;
std::cin>>a;
ai = a;
if(m==3||m==2)
 i=a;

std::cout<<"\nEnd point: "<<std::endl;
std::cin>>b;
bi = b;
if(m==3||m==2)
  j=b;

//ask for more input depend on type of calculation
//use a function to do the calculation
switch (m)
{
 case 1:
  {
   std::cout<<"\nNumber of rectangles: "<<std::endl;
   std::cin>>nR;
   std::cout<<"\nThe sum area of the rectangles is "<<Rec(a, b, nR)<<" on the inteval "<<ai<<" to "<<bi<<" with\n "<<nR<<" rectangles used\n";
   break;
  }
 case 2:
  {
   std::cout<<"\nNumber of trapezoids: "<<std::endl;
   std::cin>>nT;
   std::cout<<"\nThe sum area of the trapezoids is "<<Trap(i,j,nT)<<" on the inteval "<<ai<<" to "<<bi<<" with\n "<<nT<<" trapeaoids used\n";
   break;
  }
 case 3:
  {
   std::cout<<"\nNumber of rectangles: "<<std::endl;
   std::cin>>nR;
   std::cout<<"\nNumber of trapezoids: "<<std::endl;
   std::cin>>nT;
   std::cout<<"\nThe sum area of the rectangles is "<<Rec(a,b,nR)<<" with "<<nR<<" rectangles used\nThe sum area of the trapezoids is "<<Trap(i,j,nT)<<" with "<<nT<<" trapezoids used\n Both are calculated on the inteval "<<ai<<" to "<<bi<<"\n";
   break;
  }
 default:
  {
   std::cout<<"\n\nInvalid input please try again\n";
   goto start;
   break;
  }
}

std::cout<<"Would you like to continue the calculation? [Y/N]";
std::cin>>re;
if(re=='Y'||re=='y')
goto start;



return 0;
}
/////////////////////////////////////////////////////////////////////////////
//                        end of main                                      //
/////////////////////////////////////////////////////////////////////////////
float Rec(float a, float b, int nR)  //calculation for rectangle
{
   float d, y;

   d=(b-a)/(float (nR)); 
   y=((float (pow(a,4)))+(float (3)))*d;
   for(int h=1; h<nR; h++)
   {
      y += (d)*(float (pow(a+d,4)) + float (3));
      a += d;
   }
if(y>0)
return (y);
else
return (-y);
}

float Trap(float i, float j, int nT) //calculation for trapezoid
{
   float e,z = 0;

   e=(j-i)/(float (nT));
   for(int k=0; k<nT; k++)
   {
      z += e*0.5*( (float (pow(i,4)))+(float (pow(i+e,4)))+(float (6)));
      i += e;
   }
if (z>0)
return (z);
else
return (-z);
}

