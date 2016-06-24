#include<iostream>
#include<cstring>

int main(int argc, char *argv[])
{
   ///////////////////// Part I ///////////////////////////
   char p;
   char *ptr = &p;
   char a[3];
   char *aptr;
   char a2[3][3];
   char *a2ptr[3];
   char **a2dptr;
   std::string str = "hello";


   for(int i=0;i<3;i++)
   {
      a2ptr[i]=new char[3];
   }
   std::cout<<std::hex;
   std::cout<<"\n/////////////////// Part I ////////////////////\n";

   std::cout<< "p address: "<<(unsigned long) &p<<std::endl;
   std::cout<< "ptr address: "<<(unsigned long) &ptr<<std::endl;
   std::cout<< "*ptr address: "<<(unsigned long) &*ptr<<std::endl;
   std::cout<< "a[] address: "<<(unsigned long) &a<<std::endl;
   std::cout<< "a[2] address: "<<(unsigned long) &a[2]<<std::endl;
   std::cout<< "aptr address: "<<(unsigned long) &aptr<<std::endl;
   std::cout<< "*aptr address: "<<(unsigned long) &*aptr<<std::endl;
   std::cout<< "a2[][] address: "<<(unsigned long) &a2<<std::endl;
   std::cout<< "a2[0][0] address: "<<(unsigned long) &a2[0][0]<<std::endl;
   std::cout<< "a2[0][2] address: "<<(unsigned long) &a2[0][2]<<std::endl;
   std::cout<< "a2[2][0] address: "<<(unsigned long) &a2[2][0]<<std::endl;
   std::cout<< "a2[2][2] address: "<<(unsigned long) &a2[2][2]<<std::endl;
   std::cout<< "a2ptr address: "<<(unsigned long) &a2ptr<<std::endl;
   std::cout<< "a2prt[] address: "<<(unsigned long) &a2ptr[0]<<std::endl;
   std::cout<< "a2ptr[][] address: "<<(unsigned long) &a2ptr[0][0]<<std::endl;
   std::cout<< "str address: "<< (unsigned long) &str<<std::endl;
   std::cout<< "str address: "<< (unsigned long) &str[0]<<std::endl;


   int z=0,i;
   do{
      if(z==0)
	 i=100;
      else
	 i=200;
      int ****p2;

      p2 = new int ***;
      *p2 = new int **;
      **p2=new int *;
      ***p2=&i;

      std::cout<< "p2 address: "<<&p2<<std::endl;
      std::cout<< "p2 value: "<<p2<<std::endl;
      std::cout<< "*p2 address: "<<&*p2<<std::endl;
      std::cout<< "*p2 value: "<<*p2<<std::endl;
      std::cout<< "**p2 address: "<<&**p2<<std::endl;
      std::cout<< "**p2 value: "<<**p2<<std::endl;
      std::cout<< "***p2 address: "<<&***p2<<std::endl;
      std::cout<< "***p2 value: "<<***p2<<std::endl;
      std::cout<< "****p2 address: "<<&****p2<<std::endl;
      std::cout<< "****p2 value: "<<****p2<<std::endl;
      std::cout<< "i: "<<i<<std::endl;
      z++;
   }while(z==1);

   std::cout<< "\n////////////////// Part III //////////////////////\n";
   std::string s;
   unsigned long n,d=0;
   std::cout<<"\nPlease enter a string: ";
   getline(std::cin,s);
   std::cout<<"You have entered " << s<<std::endl;
   n=s.length();
   char c[n],temp;
   char *sptr;
   strcpy(c,s.c_str());
   int k = ((n + 1 ) / 2);
   for(d=0;d<=k;d++)
   {
      sptr=&c[d];
      temp=*sptr;
      *sptr=c[n-d-1];
      c[n-d-1]=temp;
   }
   /*
   int f=0,g=n-1;
   while (f!=g&&f<g)
   {
      sptr=&c[f];
      temp=*sptr;
      *sptr=c[g];
      c[g]=temp;
      f++;
      g--;
   }
   */

   std::cout<<c<<"\n"<<std::endl;

   std::cout<< "\n////////////////// End of the Lab  //////////////////////\n";









   return 0;
}
