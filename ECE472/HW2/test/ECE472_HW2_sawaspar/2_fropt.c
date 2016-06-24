#include "1_frexp.c"

//Prototype
double bare_subtract(double a, double b);

void __bare_parse(double val, uint64_t *lval, uint64_t *lval_sign, uint64_t *lval_expo, uint64_t *lval_frac){
   //Converting to unsigned long for bit pattern
   (*lval) = *((uint64_t*) &val);
   //Extracting the signed bit
   (*lval_sign) = (((*lval)>>30)>>30)>>3;
   //Extracting the exponent and getting rid of sign_bit
   (*lval_expo) = (( ((*lval) & ~(((1l<<30)<<30)<<3)) >>30)>>22);
   //Extracting the fraction (Mantissa)
   (*lval_frac) = ((*lval)<<12)>>12;

   return;
}

double bare_add(double a, double b){
   uint64_t la ;
   uint64_t lb ;
   uint64_t la_sign ;
   uint64_t lb_sign ;
   uint64_t la_expo ;
   uint64_t lb_expo ;
   uint64_t la_frac ;
   uint64_t lb_frac ;
   uint64_t diff_expo = 0;
   uint64_t lc_sign ; 
   uint64_t lc_expo ;
   uint64_t lc_frac ;

   __bare_parse(a, &la, &la_sign, &la_expo, &la_frac);
   __bare_parse(b, &lb, &lb_sign, &lb_expo, &lb_frac);

   lc_sign = la_sign ^ lb_sign;

   //printf("bare_add    : %#lf, %#lf\n",*((double*) &la), *((double*) &lb));

   //Take care of the sign
   if(lc_sign){
      if(la_sign){
	 return bare_subtract(b,-a);
      }else if(lb_sign){
	 return bare_subtract(a,-b);
      }
   }else {

      //Different Exponential
      if(la_expo > lb_expo){
	 diff_expo = la_expo - lb_expo;
	 lb_frac = (lb_frac | ((1l<<30)<<22) )>>diff_expo;
	 lc_expo = la_expo;
	 lc_frac = la_frac + lb_frac;
	 if( ((1l<<30)<<22) & lc_frac ){
	    lc_expo++;
	    lc_frac &= ~((1l<<30)<<22);
	    lc_frac = lc_frac>>1;
	 }
      }else if(lb_expo > la_expo){
	 diff_expo = lb_expo - la_expo;
	 la_frac = (la_frac | ((1l<<30)<<22) )>>diff_expo;
	 lc_expo = lb_expo;
	 lc_frac = la_frac + lb_frac;
	 if( ((1l<<30)<<22) & lc_frac ){
	    lc_expo++;
	    lc_frac &= ~((1l<<30)<<22);
	    lc_frac = lc_frac>>1;
	 }
	 //Same Exponential
      }else if(lb_expo == la_expo){
	 lc_expo = la_expo;
	 lc_frac = la_frac + lb_frac;
	 if( ((1l<<30)<<22) & lc_frac ){
	    lc_expo++;
	    lc_frac = lc_frac>>1;
	 }
	 lc_expo++;
	 lc_frac = lc_frac>>1;
      }
      //Reconstructing the bit pattern
      //   reconst = (temp_sign<<63) | (temp_expo<<52) | (temp_frac<<0);  
      uint64_t reconst =0; 
      reconst |= (((lc_sign<<30)<<30)<<3);
      reconst |= ((lc_expo<<30)<<22); 
      reconst |= (lc_frac<<0);  
      //Setting the output
      double ret_frac = *((double*) &reconst);  

      return ret_frac; 

   }
}


double bare_subtract(double a, double b){
   uint64_t la ;
   uint64_t lb ;
   uint64_t la_sign ;
   uint64_t lb_sign ;
   uint64_t la_expo ;
   uint64_t lb_expo ;
   uint64_t diff_expo = 0;
   uint64_t lc_sign ; 
   uint64_t lc_expo ;
   uint64_t first_dig = 0;
   uint64_t one = ((1l<<30)<<30)<<3;
   signed long la_frac ;
   signed long lb_frac ;
   signed long lc_frac ;

   __bare_parse(a, &la, &la_sign, &la_expo, &la_frac);
   __bare_parse(b, &lb, &lb_sign, &lb_expo, &lb_frac);


   //In case of different sign (+a,-b) or (-a,+b)
   //Basically, just add them and take care of the end result sign
   if(la_sign ^ lb_sign){
      if(lb_sign){
	 return bare_add(a,-b);
      }else if(la_sign){
	 return ((double)(-1))*bare_add(-a,b);
      }
   }

   //In case of the same sign (+a,+b) or (-a,-b)
   if(la_expo > lb_expo){
      //Use expo of a as a standard
      //printf("bare_sub    : %#lf, %lf\n", a, b);
      lc_expo = la_expo;
      //Adjusting to be the same expo
      diff_expo = la_expo - lb_expo;
      la_frac |= ((1l<<30)<<22);
      lb_frac = ( ((1l<<30)<<22) | lb_frac)>>diff_expo;

      lc_frac = la_frac - lb_frac;

   }else if(lb_expo > la_expo){
      //Use expo of a as a standard
      //printf("bare_sub    : %#lf, %lf\n", a, b);
      lc_expo = lb_expo;
      //Adjusting to be the same expo
      diff_expo = lb_expo - la_expo;
      lb_frac |= ((1l<<30)<<22);
      la_frac = ( ((1l<<30)<<22) | la_frac)>>diff_expo;

      lc_frac = lb_frac - la_frac;

      lc_sign |= 1<<0;

   }else{
      //printf("bare_sub    : %#lf, %lf\n", a, b);
      lc_expo = lb_expo + 1;
      //Adjusting to be the same expo
      diff_expo = 0;
      la_frac = ( ((1l<<30)<<22) | la_frac)>>1;
      lb_frac = ( ((1l<<30)<<22) | lb_frac)>>1;

      lc_frac = lb_frac - la_frac;
      lc_sign &= 0L;

   }

   //printf("lc_frac: %#lx\n",lc_frac);
   if(lc_frac < 0){
      //	 printf("Y U SO NEG?@!?\n");
      lc_frac *= ((signed long)(-1));
      lc_sign ^= 1<<0;
   }
   //    printf("lc_frac_at:  %#ld\n",lc_frac);
   while(!(lc_frac & one) && (first_dig<65)){
      // printf("first_dig: %#ld, lc_frac: %#lx, one: %#lx\n",first_dig,lc_frac, one);
      one = one >> 1;
      first_dig++;
   }
   //In case Matissa never exist
   if(first_dig==65)
      first_dig = 53;
   //Expo different comparing to 52 (-11)
   diff_expo = first_dig - 11;
   //First digit found
   first_dig = 63-first_dig ;

   if(first_dig < 52){
      lc_expo -= diff_expo;
      lc_frac = lc_frac << diff_expo;
   }else{
      lc_expo += diff_expo;
      lc_frac = lc_frac >> diff_expo;
   }	
   //printf("first_dig: %#lx, diff_expo: %#lx, lc_frac: %#lx\n", first_dig, diff_expo, lc_frac);
   lc_frac &= ~((1l<<30)<<22); 

   //Reconstructing the bit pattern
   //   reconst = (temp_sign<<63) | (temp_expo<<52) | (temp_frac<<0);  
   uint64_t reconst =0; 
   reconst |= (((lc_sign<<30)<<30)<<3);
   reconst |= ((lc_expo<<30)<<22); 
   reconst |= (lc_frac<<0);  
   //Setting the output
   double ret_frac = *((double*) &reconst);  

   return ret_frac; 
}

double bare_multiply(double a, double b){
   uint64_t la ;
   uint64_t lb ;
   uint64_t la_sign ;
   uint64_t lb_sign ;
   uint64_t la_expo ;
   uint64_t lb_expo ;
   uint64_t la_frac ;
   uint64_t lb_frac ;
   uint64_t diff_expo = 0;
   uint64_t lc_sign ; 
   uint64_t lc_expo ;
   uint64_t lc_frac ;
   uint64_t one = ((1l<<30)<<30)<<3;
   //printf("bare_mult   : %#lf, %#lf\n", a,b);
   __bare_parse(a, &la, &la_sign, &la_expo, &la_frac);
   __bare_parse(b, &lb, &lb_sign, &lb_expo, &lb_frac);


   //Calculating the sign bit
   lc_sign = la_sign ^ lb_sign;

   //Calculating the exponent
   lc_expo = (la_expo-((uint64_t)1023)) + (lb_expo -((uint64_t)1023));
   // printf("lc_expo:  %#lx\n",lc_expo);

   //Calculating the mantissa (sorry the rest 30bits, can't make it)
   lc_frac = 0;
   lc_frac = ((1l<<23)|(la_frac>>29)) * ((1l<<23)|(lb_frac>>29));
   //printf("lc_frac:  %#lx\n",lc_frac);
   uint64_t first_dig = 0;
   //uint64_t mask = one; 
   while(!(lc_frac & one)){
      //      printf("in: %#lx, lc_frac: %#lx, mask: %#lx\n",first_dig,lc_frac, mask);
      one = one >> 1;
      first_dig++;
   }
   first_dig = 63-first_dig;
   //printf("1st dig: %#lx\n", first_dig);
   //   diff_expo = ((uint64_t) 52-diff_expo) - ((uint64_t) 29);
   if(first_dig < 23 ){
      lc_frac = lc_frac << (23-first_dig);
      lc_frac &= ~(1l<<(23-first_dig));
   }else{
      lc_frac = lc_frac >> (first_dig-23);
      lc_frac &= ~(1l<<(first_dig-23));
   }
   //printf("lc_frac:  %#lx\n",lc_frac);

   //Reconstructing the bit pattern
   uint64_t reconst =0; 
   reconst |= (lc_sign<<31); 
   reconst |= ((uint64_t)lc_expo+(uint64_t)127)<<23; 
   reconst |= (((uint64_t)lc_frac)<<0);  
   //Setting the output
   float ret_frac = *((float*) &reconst);  

   return ret_frac; 
}



double bare_division(double a, double b){
   uint64_t la ;
   uint64_t lb ;
   uint64_t la_sign ;
   uint64_t lb_sign ;
   uint64_t la_expo ;
   uint64_t lb_expo ;
   uint64_t la_frac ;
   uint64_t lb_frac ;
   uint64_t diff_expo = 0;
   uint64_t lc_sign = 0 ; 
   uint64_t lc_expo ;
   uint64_t lc_frac ;
   uint64_t one = (1L<<63);


   //printf("bare_divs   : %#lf, %#lf\n", a,b);
   __bare_parse(a, &la, &la_sign, &la_expo, &la_frac);
   __bare_parse(b, &lb, &lb_sign, &lb_expo, &lb_frac);

   //Calculating the sign bit
   lc_sign = la_sign ^ lb_sign;

   //Calculating the exponent
   lc_expo = (la_expo-((uint64_t)1023)) - (lb_expo -((uint64_t)1023));
   // printf("lc_expo:  %#lx\n",lc_expo);

   //Padding the magic 1
   la_frac |= (1L<<52);
   lb_frac |= (1L<<52);

   //Back to basic, Using long division
   for(uint8_t i = 0; i<53; ++i){
      if(la_frac >= lb_frac){
	 lc_frac = ((lc_frac<<1)|(1<<0));
	 la_frac -= lb_frac;
      }else{
	 lc_frac <<= 1;
      }
      lb_frac >>= 1;
   }

   uint64_t first_dig = 0;
   while(!(lc_frac & one)){
      one = one >> 1;
      first_dig++;
   }

   //In case Matissa never exist
   if(first_dig==65)
      first_dig = 53;
   //Expo different comparing to 52 (-11)
   diff_expo = first_dig - 11;
   //First digit found
   first_dig = 63-first_dig ;


   if(first_dig < 52){//That works!
      lc_expo -= diff_expo;
      lc_frac = lc_frac << diff_expo;
   }else{
      lc_expo += diff_expo;
      lc_frac = lc_frac >> -diff_expo;
   }	
   //printf("first_dig: %#lx, diff_expo: %#lx, lc_frac: %#lx\n", first_dig, diff_expo, lc_frac);
   lc_frac &= ~((1l<<30)<<22); 

   uint64_t reconst =0; 
   reconst |= (((lc_sign<<30)<<30)<<3);
   reconst |= (((lc_expo+1023)<<30)<<22); 
   reconst |= (lc_frac<<0);  
   //Setting the output
   double ret_frac = *((double*) &reconst);  

   return ret_frac; 
}


double bare_sqrt(double a){
   uint64_t la  = *((uint64_t*) &a);
   //printf("bare_sqrt   : %#lf\n", a);
   la -= (1l<<52);
   la >>= 1l; //That's cool you can do this
   la += 1l<<61;
   //Calibrate for the value range precision on more than 2
   la &= ~(0x0000FFFFFFFFFFFFL);
   return (*(double*) &la);
}
//(Source: Wikipedia Methods_of_computing_square_roots)
