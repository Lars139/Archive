#include<iostream>
#include<cmath>
int main()
{
int n,s;
std::cout<<"Function: x^5 + 10\n""the summation will begin from 1 to n\n""please insert the n value\n""n = ";
std::cin>>n;

for(int i=0 ;i<n;i++)
{
s += pow(i,5)+10;
}
/*
int i = 0;
while(i<n)
{
s+= pow(i,5)+10;
i++;
}*/
std::cout<<"The result is "<<s<<std::endl;

//I personally prefer for loop because it's easier to read.



return 0;
}
