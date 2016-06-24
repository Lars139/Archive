#include<iostream>
void CountA(int b);
void CountD(int b);
void CountB(int a, int b);
int i;
char d;
int main()
{
   do{
   int a, b,c;
  
start:
   std::cout<<"Please enter two integer(the first number must be smaller than the second number: ";
   std::cin>>a;
   std::cin>>b;

   if(a<b&&a!=0&&a>0&&b>0)
   {
     CountA(b);
     CountD(b);
     CountB(a,b);
  
   }
   else
   {
      std::cout<<"Invalid number(s) please try again\n";
      goto start;
   }
   std::cout<<"Would you like to continue[y/n]?\n";
   std::cin>>d;
   }while(d=='y');
   return 0;
}
/////////////function
//count from 0 to b
void CountA(int b)
{
for(i=0;i<=b;i++)
      {
        std::cout<<i;
      }
std::cout<<"\n";
}

//count from b to 0
void CountD(int b)
{
   for(i=b;i>=0;i--)
   {
      std::cout<<i;
   }
   std::cout<<"\n";
}

//count from a to b
void CountB(int a, int b)
{
   
   for(i=a;i<=b;i++)
   {
      std::cout<<i;
   }
   std::cout<<"\n";
   
}
