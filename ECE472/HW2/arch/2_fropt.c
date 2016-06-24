#include "1_frexp.c"


void __bare_parse(double val, uint64_t *lval, uint64_t *lval_sign, uint64_t *lval_expo, uint64_t *lval_frac){
   //Converting to unsigned long for bit pattern
   (*lval) = *((uint64_t*) &val);
   //Extracting the signed bit
   (*lval_sign) = (((*lval)>>30)>>30)>>3;
   //Extracting the exponent and getting rid of sign_bit
   (*lval_expo) = (( ((*lval) & ~(((1<<30)<<30)<<3)) >>30)>>22);
   //Extracting the fraction (Mantissa)
   (*lval_frac) = ((*lval)<<12)>>12;

   return;
}

double bare_add(double a, double b, int *exp){
   uint64_t la ;
   uint64_t lb ;
   uint64_t la_sign ;
   uint64_t lb_sign ;
   uint64_t la_expo ;
   uint64_t lb_expo ;
   uint64_t la_frac ;
   uint64_t lb_frac ;

   __bare_parse(a, &la, &la_sign, &la_expo, &la_frac);
   __bare_parse(b, &lb, &lb_sign, &lb_expo, &lb_frac);

   printf("\nla: %#lx\n", la);
   printf("la_lf: %#lf\n",*((double*) &la));
   printf("lb: %#lx\n", lb);
   printf("lb_lf: %#lf\n\n",*((double*) &lb));

   //Determining the signed bit of the result
   uint64_t lc_sign = la_sign ^ lb_sign;

   //FIXME: HERE?
   //Converting the expo to be the same before adding
   uint64_t diff_expo = 0;
   if(la_expo > lb_expo){
      diff_expo = la_expo - lb_expo;
      lb_frac = (((1<<30)<<22) | lb_frac) >> diff_expo;
      lb_expo += diff_expo;
   }else if(lb_expo > la_expo){
      diff_expo = lb_expo - la_expo;
      la_frac = (((1<<30)<<22) |la_frac) >>diff_expo;
      la_expo += diff_expo;
   }

   printf("diff_expo: %#lx\n", diff_expo);
   printf("la_expo_exp: %#lx\n", la_expo); 
   printf("la_frac_exp: %#lx\n", la_frac); 
   printf("lb_expo_exp: %#lx\n", lb_expo); 
   printf("lb_frac_exp: %#lx\n", lb_frac); 
   printf("\nlc_sign: %#lx\n\n", lc_sign); 

   //Determining the expo of the result
   uint64_t lc_expo = la_expo;
   uint64_t lc_frac = 0;

   //Adding Mantissa
   if(lc_sign){ //neg vs pos
      if(a > b){
	 //TODO: a subtract b;
	 printf("a sub b");
      }else{
	 //TODO: b subtract a;
	 printf("b sub a");
      }
   }else{
      //lc_frac = (((la_frac|((1<<30)<<22)) + (lb_frac|((1<<30)<<22))) >>1);
      lc_frac = (la_frac + lb_frac);
      if(lc_frac & ((1<<30)<<22)){
	 lc_expo++;
	 if(diff_expo){
	    lc_frac &= ~((1<<30)<<22);
	 }else{
	    lc_expo++;
	 }
	 lc_frac = lc_frac>>1;
      }
      /*lc_frac = (la_frac + lb_frac) ;

	printf("la_frac_add: %#lx\n", la_frac); 
	printf("la_expo_add: %#lx\n", la_expo); 
	printf("lb_frac_add: %#lx\n", lb_frac); 
	printf("lb_expo_add: %#lx\n", lb_expo); 
	printf("lc_frac_add: %#lx\n", lc_frac); 

	lc_frac = lc_frac>>1 ;
      //      printf("lc_frac_shf: %#lx\n", lc_frac); 
      */

   }

   /*   printf("la_expo: %#lx\n", la_expo); 
	printf("lb_expo: %#lx\n", lb_expo); 
	printf("la_frac: %#lx\n", la_frac); 
	printf("lb_frac: %#lx\n", lb_frac); 
	*/

   printf("lc_frac: %#lx\n", lc_frac);
   printf("lc_expo: %#lx\n", lc_expo);


   //Reconstructing the bit pattern
   //   reconst = (temp_sign<<63) | (temp_expo<<52) | (temp_frac<<0);  
   uint64_t reconst =0; 
   reconst |= (((lc_sign<<30)<<30)<<3);
   reconst |= ((lc_expo<<30)<<22); 
   reconst |= (lc_frac<<0);  
   printf("reconst: %#lx\n", reconst);

   //Setting the output
   *exp = lc_expo-1023;
   double ret_frac = *((double*) &reconst);  

   return ret_frac; 

}
