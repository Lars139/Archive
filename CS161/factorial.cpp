#include<iostream>
#include<sys/time.h>
#include<cstdlib>
////start function factorial
int facR(int n)
{
   if(n==0)
      return 1;
   else
      return n*facR(n-1);
}

int facI(int n)
{
   int a=n;
   if(n==0)
      return 1;
   else
      for(int i =1;i<a;i++)
      {
          n*=(a-i);
      }
   return n;
} 

////start main
int main()
{
   struct timeval stop, start;
   int n=0;
   char x;
   do{
   std::cout<<"Please enter the factorial number: ";
   std::cin>>n;
   gettimeofday(&start, NULL);
   std::cout<<facR(n)<<std::endl;
   gettimeofday(&stop, NULL);
   std::cout<<"Time: "<<stop.tv_usec - start.tv_usec<<std::endl;
   std::cout<<"Continue?[y/n]: ";
   std::cin>>x;
   }while(x=='y'||x=='Y');

return 0;
}
