/*Author: Rattanai Sawaspanich
 * Date:  Sat,28 Jan 2014
 * Note:  This program was set default to ULONG_MAX
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define YELLOW "\x1b[33m"
#define NC "\x1b[0m"
#define ST 20 
//ST is the number of the maximun that a specific type can have. 
//EX: unsigned long is 10 digits

/*Func: is_overflow(unsigned long)
 * check if an input number is going to cause an overflow of type unsigned long
 * if it overflows, return 1;
 * if not, return 0;
 */

int is_overflow(char *ch,int j){
	char UL[ST];
	unsigned long a=ULONG_MAX, b=0;
	if(j<ST)
		return 0;

	for(;j>0;--j){//convert ULONG_MAX to array of char
		b=a/10;
		b*=10;
		UL[j-1] = (a-b)+'0';
		a/=10;
	}

	/*printf("overflow UL_MAX: ");
	for(int i=0;i<ST;i++)
		printf("%c",UL[i]);
		*/

	for(int i=0;i<ST;++i){//check for overflow
		if((ch[i]-'0') > (UL[i]-'0') ) 
		{
			printf(YELLOW"The input number will cause an overflow.\n" "Program is now existing...\n" NC);
			exit(EXIT_FAILURE);
		}else if((ch[i]-'0') < (UL[i]-'0') )
			return 0;
		else if((ch[i]-'0') == (UL[i]-'0') )
		{
			//Intentionally left blank
		}	
	}
	return 1;
}

/*Func: digitize();
 * Check if the input string is a number. 
 * If the string input is not entirely composed of number, extract the number digits from the string and return the number.
 * If the whole string contains no digits, the function will exit the program with EXIT_FAILURE
 *
 * Note: This function takes care of negative number, character input, and zero input for the program. 
 */
unsigned long digitize(char *c){ 
	char temp[ST]; 
	int j=0,k=0;
	unsigned long num=0;

	for(int i=0;i<ST;++i)//initialize temp var
		temp[i] = '0';

	for(int i=0; i<ST;++i){ //extract digits
		if( (c[i]-'0')>=0 && (c[i]-'0')<=9 ){
			temp[j] = c[i];
			++j;
		}
	}

	is_overflow(temp,j);

	for(;j>=0;--j){ //turn digits into u_long
		num += (temp[j]-'0')*((unsigned long)pow(10,k-1)); //tricky tricky  pow() only goes up to 10^16, so if the number bigger than that it acts weird. It took me an hour to figure this out.
		k++;

	}
	if(num==0){
		printf(YELLOW"The input sting must contain at least a numeral.\n" "Program is now existing...\n" NC);
		exit(EXIT_FAILURE);
	}

	return num;
}

void prompt( unsigned long *max, int p, char *in_num){
	//char inp[ST];
	unsigned long lnum=0;
	while(p==1){ //just making sure that the invalid number shall not pass
		lnum = 0;
		printf("Please input the upper limit: ");
		scanf("%20[^\n]",in_num); //FIXME: Change 10 to size of ST
		lnum = digitize(in_num); //convert string input to a long-type number
		if(lnum!=0)
			p=0;
		else
			p=1;
	}
	if(p==0){ //command line successful
		lnum = digitize(in_num);
	}
	*max = lnum;
	return;
}


void cmd_handling(int argc, char **argv, char *in_num, int *p){
	if(argc<3){
		*p=1;
		printf(YELLOW"The command line argument did not provided enough information.\n"NC);
	}else if(argc>=3){
		if(argc>3){
			printf(YELLOW"Warning: command line argument besides \"-n\" will be ignored.\n"NC);
		}
		for(int i=0;i<argc;++i){
			if(!strcmp((argv[i]),"-n")){//if the string finds "-n"
				for(int j=0;argv[i+1][j]!='\0';++j){ //copy the string input to in_num for the further checking
					in_num[j] = argv[i+1][j];
				}
			}
		}

			/*printf("in_num: ");
		for(int i=0; in_num[i]!='\0';++i){
			printf("%c",in_num[i]);
		}
			printf("\n\n"); */

	}else{
		printf(YELLOW"The command line argument has corrupted.\n" "Program is now existing...\n" NC);
		exit(EXIT_FAILURE);
	}
	return;
}
/*Func: add_n()
 * This function add a number to a given index of the arry
 * If the array is too small, double its size
 * If the array is ok, add the number to the given index
 */

void add_n(unsigned long**pr,unsigned long*cap,unsigned long *size,unsigned long inx, unsigned long num){
	(*size)++;
unsigned long i=0;
	if((*size)>(*cap)){
		//resize the arr
		unsigned long* temp = malloc(sizeof(unsigned long)*(*cap)*2);
		//unsigned long* old = pr;
		if(temp==NULL||malloc(sizeof(unsigned long)*(*cap)*2)==NULL
){
			printf(YELLOW"The error has occured with malloc.\n" "Program is now exiting...\n" NC);
			exit(EXIT_FAILURE);
		}

		for(;i<(*cap);++i)
			temp[i] = (*pr)[i];
		temp[i+1]=num;
		(*cap)*=2;
		*pr = temp;
		//free(old);
		if(pr==NULL){
			printf(YELLOW"The error has occured during array resizeing.\n" "Program is now exiting...\n" NC);
			exit(EXIT_FAILURE);
		}
/*		printf("Bigger size: %lu\n",*size);
		printf("Bigger cap: %lu\n",*cap);
		printf("Bigger inx: %lu\n",inx);
		*/
	}else{
/*		printf("size: %lu\n",*size);
		printf("cap: %lu\n",*cap);
		printf("inx: %lu\n",inx);
		*/
		(*pr)[inx] = num;
	}
}

/*Func: ini_arr()
 * This function dealing with dynamic array size and setting up array ready to for a prime() to use.
 */

void ini_arr(unsigned long **pr,unsigned long*cap, unsigned long *size, unsigned long max){

	(*pr) = malloc(sizeof(unsigned long)*(*cap));

	for(unsigned long i=2;i<max;i++){
		add_n(pr,cap,size,i-2,i);//put 1 to max to an array
	}
	if(pr==NULL){
		printf(YELLOW"Program failed to allocate array of number upto a given boundary.\n" "Program is now existing...\n" NC);
		exit(EXIT_FAILURE);
		}
		return;
}

/*Func: prime()
 * this function basically chagne the number in an array that is not a prime number to zero
 */

void prime(unsigned long *pr,unsigned long max){//Let's the hunt begin
	for(int i=1;i<max;++i){
		for(int j=1;j<max;++j){
			if(pr[j] != 0 && pr[i] != 0 && pr[j]%pr[i]==0 && i!=j || pr[j]%4==0)
				pr[j] = 0;
		}
	}
}

/*Func: print_arr()
 * This function will print an array for you
 * This function will also counts how many element are there that is not zero
 */
void print_arr(unsigned long *pr, unsigned long cap){
	unsigned long cnt=0;
	int n=0;
	for(unsigned long i=0; i<cap;++i){
		if(pr[i]!=0){
			cnt++;
			n++;
			printf(" %lu ",pr[i]);
			if(n%3==0){
				printf("\n");
				n=0;
			}

		}
	}

				printf("\nThere is total of %lu prime numbers\n",cnt);
}


int main(int argc, char *argv[]){
	unsigned long max;
	unsigned long *pr=0;
	char in_num[ST];
	int p=0;
	unsigned long size=0, cap=ST;

	cmd_handling(argc,argv,in_num,&p);
	prompt(&max,p,in_num);
	ini_arr(&pr,&cap,&size,max);
	prime(pr, cap);
	print_arr(pr,cap);
	return 0;
}
