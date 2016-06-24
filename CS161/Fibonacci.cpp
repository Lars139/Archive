#include<iostream>
#include<sys/time.h>
#include<cstdlib>
#include<string>
/// Begin the iterative function
///************************************************
//Program: Fibonacci
//Author: Rattanai Sawaspanich
//Date: 11/4/2012
//Description:  The higher the n goes, the longer it will take to calculate
//Input:Fibonacci number to calculate ---n
//      Character to determine if user wants to continue.
//Output:Error message
//       Time of execution for each solution
//       corresponding Fibonacci number
//**************************************************
int fib_iter(int n)
{
   int a=1,b=0,f=0;
   for(int i=-1;i<n;i++)
   {
      if(i!=-1)
      {
	if(i%2==0)
	{
	   a=f;
	}
	else
	{
	   b=f;
	}
      }
        f+=(a+b-f);
   }
   return f;
}

/// Begin recursive function
int fib_recurs(int n)
{
   int c,d;
   if(n==0||n==1)
      return 1;
   else
   {
      return fib_recurs(n-1)+fib_recurs(n-2);
   }   
}

///Function testing if it is an integer
void test(std::string ch);
/// Begin main function
int main()
{
   int n;
   std::string ch,yn,h;
   struct timeval stop, start;
input:
   std::cout<<"\nPlease enter the number: ";
   std::cin>>ch;
   
   h=ch.substr(0,1);
   for(int i=0;h!="\0";i++)
   {
      if(!(h=="1"||h=="2"||h=="3"|h=="4"||h=="5"||h=="6"||h=="7"||h=="8"||h=="9"||h=="0"))
      {
	 std::cout<<"\nPlease input a valid integer";
	 goto input;
      }
      h=ch.substr(i,1);
   }

   n=atoi(ch.c_str());
   if(n<0)
   {
      std::cout<<"\nPlease input a positive integer";
      goto input;
   }
   if(n>45)
   {
      std::cout<<"\nPlease input a lesser positive integer (Overflow)";
      goto input;
   }
gettimeofday(&start, NULL);
   fib_recurs(n);
gettimeofday(&stop, NULL);
   std::cout<<"Your "<<n<<"th Fibonacci is "<<fib_recurs(n)<<std::endl;
   std::cout<<"Recursive Time: "<<stop.tv_usec - start.tv_usec<<std::endl;
gettimeofday(&start, NULL);
   fib_iter(n);
gettimeofday(&stop, NULL);
   std::cout<<"Your "<<n<<"th Fibonacci is "<<fib_iter(n)<<std::endl;
   std::cout<<"Iterative Time: "<<stop.tv_usec - start.tv_usec<<std::endl;
   std::cout<<"\nWould you like to continue? [y/n]";
   std::cin>>yn;
   if(yn=="y"||yn=="Y")
      goto input;
   return 0;
}



