#include<iostream>
#include<string>
#include<cmath>
#define pi 3.14159265358979323
int main()

{


	std::string t,n;

/*****************************************************************
 *Function:  Calculate volume/area of the geometry shapes: Circle, Rectangle, Triangle, and Trapezoid.
*Description: as shown above
*Parameters: std::cout, std::cin, std::endl, float, int, std::string, if, else, else if
*Pre-conditions: raw value data
*Post-condition: volume adn area of shapes.
*/

std::cout<<"____________________________________________________________________\n\n";

std::cout<<"  Program: shape\n";

std::cout<<"  Author: Rattanai Sawaspanich \n";

std::cout<<"  Date: 10/10/2012\n";
std::cout<<"  Input: String, Real Number\n";
std::cout<<"  Output: Real number\n";
std::cout<<"  Description: \n  1.You can type the first word of the choices down or type only the number \n  in front of the chioces -- either one works. \n  2.You can use command \"end\" to quit the program during the time you are \n   choosing choices.\n  3.For Prisms please type only the type of shape\n  example: rectangle prism ---> rectangle\n";

std::cout<<"____________________________________________________________________\n";
start:
int c=0;
float r,z, w, h, l;
shape:  

std::cout<<"\nPlease choose what would you like to calculate: 1.Area 2.Volume 3.Both\n";
std::cin>>t;
calc:
if(t.compare("Area")==0 ||t.compare("area")==0||t.compare("1.Area")==0||t.compare("1.area")==0 ||t.compare("1")==0) 

{
	std::cout<<"\nPlease choose a shape: 1.Circle, 2.Rectangle, 3.Trapezoid, 4.Triangle\n";
	std::cin>>n;
	c=1;

}

else if(t.compare("Volume")==0||t.compare("2")==0||t.compare("volume")==0||t.compare("2.Volume")==0||t.compare("2.volume")==0)

{

	std::cout<<"\nPlease choose a shape: 1.Sphere, 2.Rectangle Prism, 3.Trapezoid Prism, \n4. Triangle Prism\n";
	std::cin>>n;
	c=2;

}

else if(t.compare("Both")==0||t.compare("3")==0||t.compare("both")==0||t.compare("3.both")==0||t.compare("3.Both")==0)

{
	std::cout<<"\nPlease choose a shape 1.Sphere/Circle, 2.Rectangle/Prism, \n3.Trapezoid/Prism, 4.Triangle/Prism\n";
	std::cin>>n;
	c=3;

}
else if(t.compare("exit")==0||t.compare("end")==0||t.compare("quit")==0)
{
goto end;
}
else
{
std::cout<<"\n               ***Please select the valid type of calculation***\n";
goto shape;
}
// end of calculation type checking. need to check if shape is valid
// If shape valid, send to the following condition and ask for more value and pring the out put.
if(n.compare("1")==0||n.compare("circle")==0||n.compare("Circle")==0||n.compare("1.circle")==0||n.compare("1.Circle")==0||n.compare("sphere")==0||n.compare("Sphere")==0||n.compare("1.Sphere")==0||n.compare("1.sphere")==0)
{
	std::cout<<"\nRadius: "<<std::endl;
	std::cin>>r;
	if(c==1)
	{
		std::cout<<"\n        Area of the circle is "<<pi*pow(r,2)<<"\n"<<std::endl;
	}
	if(c==2||c==3)
	{
		if(c==3)
			std::cout<<"\n        Area of the circle is "<<pi*pow(r,2)<<"\n"<<std::endl;
		std::cout<<"\n        Volume of the sphere is "<<(pow(r,3)*pi*(float) (4))/(float)(3)<<"\n"<<std::endl;
	}
}
else if(n.compare("2")==0||n.compare("rectangle")==0||n.compare("Rectangle")==0||n.compare("2.rectangle")==0||n.compare("2.Rectangle")==0)
{
	std::cout<<"\nWidth: "<<std::endl;
	std::cin>>w;
	std::cout<<"\nLength: "<<std::endl;
	std::cin>>l;
	if(c==1)
	{
		std::cout<<"\n        Area of the rectangle is "<<l*w<<"\n"<<std::endl;
	}
	if(c==2||c==3)
	{
		std::cout<<"\nHeight: "<<std::endl;
		std::cin>>h;
		if(c==3)
			std::cout<<"\n        Area of the rectangle is "<<l*w<<"\n"<<std::endl;
		std::cout<<"\n        Volumn of the rectangle prism is "<<l*w*h<<"\n"<<std::endl;
	}
}
else if(n.compare("3")==0||n.compare("Trapezoid")==0||n.compare("3.Trapezoid")==0||n.compare("3.trapezoid")==0||n.compare("trapezoid")==0)
{
	std::cout<<"\n1st Base: "<<std::endl;
	std::cin>>w;
	std::cout<<"\n2nd Base: "<<std::endl;
	std::cin>>l;
	std::cout<<"\nBase Height: "<<std::endl;
	std::cin>>h;
	if(c==1)
	{
		std::cout<<"\n       Area of the trapezoid is "<<(0.5)*(w+l)*(h)<<"\n"<<std::endl;
	}
	if(c==2||c==3)
	{
		std::cout<<"\nPrism Height: "<<std::endl;
		std::cin>>z;
		if(c==3)
			std::cout<<"\n       Area of the trapezoid is "<<(0.5)*(w+l)*(h)<<"\n"<<std::endl;
		std::cout<<"\n       Volume of the trapezoid is "<<(0.5)*(w+l)*h*z<<"\n"<<std::endl;
	}
}
else if(n.compare("4")==0||n.compare("Triangle")==0||n.compare("triangle")==0||n.compare("4.triangle")==0||n.compare("4.Triangle")==0)
{
	std::cout<<"\nBase: "<<std::endl;
	std::cin>>w;
	std::cout<<"\nBase Height: "<<std::endl;
	std::cin>>h;
	if(c==1)
	{
		std::cout<<"\n       Area of the triangle is "<<(0.5)*(w*h)<<"\n"<<std::endl;
	}
	if(c==2||c==3)
	{
	std::cout<<"\nPrism Height: "<<std::endl;
	std::cin>>z;
		if(c==3)
			std::cout<<"\n               Area of the triangle is "<<(0.5)*(w*h)<<"\n"<<std::endl;
	std::cout<<"\n               Volume of the triangle prism is "<<(0.5)*(w*h)*z<<"\n"<<std::endl;
	}
}
else if(n.compare("end")==0||n.compare("exit")==0)
{
	goto end;
}
else
{
	std::cout<<"\n          ***Please input the valid shape***\n\n";
	goto calc;
}
std::cout<<"Would you like to continue a shape calculation?[Y/N]"<<std::endl;
std::cin>>t;
//check if the user wants to coninue using the program
if(t.compare("yes")==0||t.compare("Y")==0||t.compare("y")==0)
{
	goto start;
}
else
{
	goto end;
}


/*



*/
end:
return 0;

}
