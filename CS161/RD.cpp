#include <iostream>

#include <cmath>


int main()

{

float i, f, t, T;

std::cout<<"\nEnter the initial amount of radioactive material:";

std::cin>> i;

std::cout <<"\nEnter the amount of time that has passed:";

std::cin>> t;

std::cout<<"\nEnter the half-life for the radioactive material:";

std::cin>> T;

std::cout<<"\n\n";

f = i/((float) pow(2,t/T));

std::cout<<"The amount of radioactive material reamaining is "<<f;
std::cout<<"\n\n";

return 0;






}
