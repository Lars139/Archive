#include<iostream>
#include<cstdlib>
int main()
{
   double *i, *j, *k, *db;  //pointers
   double a=7.8,b=10.0,c=.009; //numbers
   
   //pointers to pointees.
   i=&a;
   j=&b;
   k=&c;

   db = &c;
   std::cout<<"value of pointers i: "<<*i<<std::endl<<"value of pointers j: "<<*j<<std::endl<<"value of pointers k: "<<*k<<std::endl<<"value of pointers db: "<<*db<<std::endl;





   return 0;
}
