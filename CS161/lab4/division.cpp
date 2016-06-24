#include<iostream>
int main()
{
int a, b;
first:
std::cout<<"Your first number: ";
std::cin>>a;
zero:
std::cout<<"\nYour second number: ";
std::cin>>b;
if (b==0)
{
	std::cout<<"\nPlease input the valid second number -- not zero\n";
	goto zero;
}
if (a>b)
{
std::cout<<"\nInt division result: "<<a/b<<std::endl;
std::cout<<"\nFloat division result: "<<((float) a/ (float) b)<<std::endl;
std::cout<<"\nMod result: "<<a%b<<std::endl<<"\n";
}
else if (a<=b)
{
std::cout<<"\nPlase input the second number larger than the first number\n";
goto first;
}
else
{
std::cout<<"\nInvalid input please try again\n";
goto first;
}


return 0;
}

