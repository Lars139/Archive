#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

   //FIXME: Can't do bit-shift over 32 bit lenght... @31 gives infi

double __frexp_valid_num(double val, uint16_t *exp){
   //Converting (double) val to (unsigned long) val to do bitwise operation
   uint64_t lval = *((uint64_t*) &val);

   //printf("lval     : %#lx\n", lval);

   //Extracting the exponent and getting Rid of sign_bit
   uint64_t temp_expo = 0;
   //   temp_expo |= ((lval & ~(1<<63))>>52) & ~(1<<11);
   temp_expo |= (( (lval & ~(((1<<30)<<30)<<3)) >>30)>>22) & ~(1<<11);
   *exp = temp_expo - 1022; //subtracting the bias (1023 -1 b/c display w/ 1/2 as a base)
   //printf("temp_expo: %#lx\n\n", temp_expo);

   //Extracting the fraction 
   uint64_t temp_frac = 0;
   temp_frac = (lval<<12)>>12;
   //printf("temp_frac: %#lx\n", temp_frac);

   //Extracting the sign bit
   uint64_t temp_sign = 0;
   //   temp_sign |= (lval & (1<<63))>>63;
   temp_sign = (lval>>30);
   temp_sign = temp_sign>>30;
   temp_sign = temp_sign>>3;
   //printf("temp_sign: %#lx\n", temp_sign);

   //Reconstructing the bit pattern
   uint64_t reconst =0;
   //   reconst = (temp_sign<<63) | (temp_expo<<52) | (temp_frac<<0);  
   reconst |= (((temp_sign<<30)<<30)<<3);
   reconst |= (((uint64_t) 0x3FE<<30)<<22); //rasing to the power of 1/2
   reconst |= (temp_frac<<0);  
   //printf("reconst  : %#lx\n", reconst);

   //TODO: IF Frac > 1 or Frac <0.5 bit shift and add expo
   //Re-interpret the bit pattern
   double frac = *((double*) &reconst);

   //printf("Frac: %lf\n", frac);

   return frac;
}

double bare_frexp(double val, uint16_t *exp){
   double temp_val; uint16_t temp_exp;
   switch( __fpclassify(val) ){
      case FP_NAN:
	 //--------------------------------------In case the input is a NaN 
	 //if(val != val)
	 *exp = 0;
	 return NAN;

      case FP_INFINITE: 
	 //--------------------------------------In case the input is an INF 
	 //if(isinf(val))
	 *exp = 0;
	 return val;

      case FP_ZERO:
	 //--------------------------------------In case the input is a Zero 
	 //if(val == 0)
	 *exp = 0;
	 return 0;

      case FP_NORMAL:
	 //--------------------------------------In case the input is a valid number 
	 return __frexp_valid_num(val, exp);
   }
}

int main(){
   uint16_t exponent;
   double   temp_val;
   double   test_val = 2345;
   printf("NaN     : %lf pow %d\n",bare_frexp( NAN ,&exponent), exponent);

   printf("1.0/0.0 : %lf pow %d\n",bare_frexp( 1.0/0.0,&exponent), exponent);

   printf("-1.0/0.0: %lf pow %d\n",bare_frexp( -1.0/0.0,&exponent), exponent);

   printf("0       : %lf pow %d\n",bare_frexp(0 ,&exponent), exponent);

   temp_val = bare_frexp((double) 2560.0,&exponent);
   printf("2560    : %lf pow %d\n", temp_val, exponent);

   temp_val = bare_frexp((double) -4.0,&exponent);
   printf("-4      : %lf pow %d\n", temp_val, exponent);


   temp_val = bare_frexp(test_val,&exponent);
   printf("%.2lf : %lf pow %d\n",test_val, temp_val, exponent);

   temp_val = bare_frexp(-1*test_val,&exponent);
   printf("-%.2lf: %lf pow %d\n",test_val, temp_val, exponent);

   //FIXME: WTF??? HOW??? Y U NO WAIT???
   // printf("exp: %d\n",exponent);
   return 0;
}
