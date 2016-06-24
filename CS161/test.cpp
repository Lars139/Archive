#include<iostream>
#include<cstdlib>
#include<string>

bool main()
{
   int i=1;
   std::string In, Ch;
   std::cin>>In;
   Ch = In.substr(0,1);
   while(Ch!="\0")
   {
      if(!(Ch=="1"||Ch=="2"||Ch=="3"||Ch=="4"||Ch=="5"||Ch=="6"||Ch=="7"||Ch=="8"||Ch=="9"||Ch=="0"))
      {
	 std::cout<<"Invalid number\n";
      return (1==0);
      }
      Ch=In.substr(i,1);
      i++;
   }
   std::cout<<"that's a valid number\n";
   return (0==0);

}
