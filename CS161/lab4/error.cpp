#include<iostream>
#include<string>
#define PROMT "Please enter a whole number: "
#define NOT_PRIME "The number is not a prime number.\n"
#define PRIME "The number is a prime number. \n"
#define DONE 0
#define FIRST_FACTOR 2
int main()
{
int number,i;
std::cout<<PROMT;
std::cin>>number;
for(i=2;i < number;i++)
{
	if( number%i==0)
	{
		std::cout<<NOT_PRIME<<number;
		return DONE;
	}
	else
	{
		std::cout<<PRIME<<number;
		return DONE;
	}
}



return 0;
}
