#include <iostream>
int main()
#define bit 8

{
int nChar, nInt, nFloat, nShort, nDouble, nBool, nLong;
nChar = sizeof(char);
nInt = sizeof(int);
nFloat = sizeof(float);
nShort = sizeof(short);
nDouble = sizeof(double);
nBool = sizeof(bool);
nLong = sizeof(long);
std::cout << "\n\n____________________________________________________\n" "A char takes up to "<<nChar*bit<<"  bits of memory\n" "A int takes up to "<<nInt*bit<<" bits of memory\n" "A float takse up to "<<nFloat*bit<<" bits of memory\n" "A short takes up to "<<nShort*bit<<" bits of memory\n" "A double takes up to "<<nDouble*bit<<" bits of memory\n" "A bool takes up to "<<nBool*bit<<" bits of memor\n" "A long takes up to "<<nLong*bit<<" bits of memory\n" "_________________________________________________\n\n";


return 0;

}
