#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

   //NOTE: Can't do bit-shift over 32 bit lenght... @31 gives infi
   //IGNORE the line above... I was being dumb

double __frexp_valid_num(double val, int *exp){
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

   //Re-interpret the bit pattern
   double frac = *((double*) &reconst);

   //printf("Frac: %lf\n", frac);

   return frac;
}

double bare_frexp(double val, int *exp){
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
