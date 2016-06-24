#include<iostream>
#include<cstdlib>
#include<cstring>
void re(char i[], int n);

int main(int x, char *in[] /* can also write as **in */ )
{
   char c;
   int n,p=0;
   std::string str;
   char i[n+1];
   //do{
   std::cout<<"Please input your sentence: \n";
   getline(std::cin,str);
   std::cout<<"what would you like to find palindrome[p], inverese string[i]";
   std::cin>>c;
   
   n = str.length();  // *.lenght() for string length
                      // strlen(array, array size) for array of string
   strcpy(i,str.c_str());
   if(c=='p'||c=='P')
   {
     for (int m=0;m<=n;m++)
      {
         if(i[m]==i[n-(m+1)]) 
         {
	    p++;
         }
      }
      if((p-1)==n)
         std::cout<<"\n***You have entered a Parlindrome***\n";
      else
         std::cout<<"\nThis is not a palindrome\n";
   }
   else if(c=='i'||c=='I')
      re(i,n);
   else
  // std::cout<<"Would you like to continue? [y/n]";
  // std::cin>>c;
  //}while(c=='y'||c=='Y');
      return 0;
   return 0;
}

void re(char i[], int n)
{
   for (int m=0;m<=n;m++)
   {
   std::cout<<i[n-(m+1)];
   }
   std::cout<<"\n";
   return;
}

