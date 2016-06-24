#include<iostream>
#define QUARTERS *0.25
#define DIMES *0.1
#define NICKLES *0.05
#define PENNIES *0.01
#define PLUS +

int main()
{
float x=3 QUARTERS PLUS 8 DIMES PLUS 4 NICKLES PLUS 11 PENNIES;
std::cout<<"I have $"<<x<<"\n";
return 0;

}
