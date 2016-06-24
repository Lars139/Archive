#include<iostream>
#include<ctime>
#include<cstdlib>

int main()
{

int n, r,x;
std::srand((time(NULL) ));
x=(rand()%50);
std::cout<<"\n\nLet's guess my number!\n";
for(n=1; n<=5; n++)
{
std::cout<<"\nYour guess: "<<std::endl;
std::cin>>r;
if(r<x)
{
	std::cout<<r<<" is too low\n";
}
else if(r>x)
{
	std::cout<<r<<" is too high\n";
}
else if(r==x)
{
	std::cout<<"You got it. Congratz!\n";
	goto end; 
}

}
std::cout<<"\nSorry try again next time\n\n";
end:
return 0;
}
