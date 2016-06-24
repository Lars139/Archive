#include <stdio.h>
#include <math.h>

int main()
{

float i, f, t, T;
printf("\nEnter the initial amount of radioactive material:");
scanf("%f",&i);
printf("\nEnter the amount of time that has passed:");
scanf("%f",&t);
printf("\nEnter the half-life for the radioactive material:");
scanf("%f",&T);
printf("\n\n");
f = i/((float) pow(2,t/T));
printf("The amount of radioactive material reamaining is %f",f);
printf("\n\n");
return 0;
}
