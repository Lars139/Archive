#include "3_fruni.c"
#define ITR_NUM 9999999
#define DEC_PLC 1000

uint64_t get_UTC_time(){
   uint32_t eax;
   uint32_t edx;
   __asm__ __volatile__("RDTSC;"
	 :"=a"(eax), "=d"(edx)
	 );			
   return ((uint64_t)eax) | ((uint64_t)edx << 32);
}

int main(){

   printf("\n\n________________________________ PART I : THE FREXP ______________________________\n\n\n");
   int exponent;
   double   temp_val;
   double   test_val = 2.5;
   printf("NaN     : %lf pow %d\n",bare_frexp( NAN ,&exponent), exponent);
   printf("1.0/0.0 : %lf pow %d\n",bare_frexp( 1.0/0.0,&exponent), exponent);
   printf("-1.0/0.0: %lf pow %d\n",bare_frexp( -1.0/0.0,&exponent), exponent);
   printf("0       : %lf pow %d\n",bare_frexp(0 ,&exponent), exponent);
   temp_val = bare_frexp((double) 2560.0,&exponent);
   printf("2560    : %lf pow %d\n", temp_val, exponent);
   temp_val = bare_frexp((double) -4.0,&exponent);
   printf("-4      : %lf pow %d\n", temp_val, exponent);
   temp_val = bare_frexp(test_val,&exponent);
   printf("%.2lf   : %lf pow %d\n",test_val, temp_val, exponent);
   temp_val = bare_frexp(-1*test_val,&exponent);
   printf("-%.2lf  : %lf pow %d\n",test_val, temp_val, exponent);

   printf("\n\n___________________________ PART II : THE OPERATIONS  ____________________________\n\n");

   uint64_t timestamps[8];
   uint64_t i=0;

   //------------------------------------------------------------------- ADD
   double a_inp = ((double)rand())/((double)(RAND_MAX/DEC_PLC));
   double b_inp = ((double)rand())/((double)(RAND_MAX/DEC_PLC));
   double h_out;
   double s_out;

   //Software x 5
   timestamps[0] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
   }
   timestamps[1] = get_UTC_time();

   //Hardware x 5
   timestamps[2] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
   }
   timestamps[3] = get_UTC_time();

   //Software x 10
   timestamps[4] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
      s_out = bare_add(a_inp, b_inp);
   }
   timestamps[5] = get_UTC_time();

   //Hardware x 10
   timestamps[6] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
      h_out = a_inp + b_inp;
   }
   timestamps[7] = get_UTC_time();

   printf("\nFor %ld interations: ADD \n",ITR_NUM );
   printf("x5  :\n");
   printf("   Software : %ld cycles, Operation Result: %#lf\n",timestamps[1]-timestamps[0], s_out );
   printf("   Hardware : %ld cycles, Operation Result: %#lf\n",timestamps[3]-timestamps[2], h_out );
   printf("x10 :\n");
   printf("   Software : %ld cycles, Operation Result: %#lf\n",timestamps[5]-timestamps[4], s_out );
   printf("   Hardware : %ld cycles, Operation Result: %#lf\n",timestamps[7]-timestamps[6], h_out );


   //------------------------------------------------------------------- SUBTRACT
    a_inp = ((double)rand())/((double)(RAND_MAX/DEC_PLC));
    b_inp = ((double)rand())/((double)(RAND_MAX/DEC_PLC));

   //Software x 5
   timestamps[0] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
   }
   timestamps[1] = get_UTC_time();

   //Hardware x 5
   timestamps[2] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
   }
   timestamps[3] = get_UTC_time();

   //Software x 10
   timestamps[4] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
      s_out = bare_subtract(a_inp, b_inp);
   }
   timestamps[5] = get_UTC_time();

   //Hardware x 10
   timestamps[6] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
      h_out = a_inp - b_inp;
   }
   timestamps[7] = get_UTC_time();

   printf("\nFor %ld interations: SUBTRACT\n",ITR_NUM );
   printf("x5  :\n");
   printf("   Software : %ld cycles, Operation Result: %#lf\n",timestamps[1]-timestamps[0], s_out );
   printf("   Hardware : %ld cycles, Operation Result: %#lf\n",timestamps[3]-timestamps[2], h_out );
   printf("x10 :\n");
   printf("   Software : %ld cycles, Operation Result: %#lf\n",timestamps[5]-timestamps[4], s_out );
   printf("   Hardware : %ld cycles, Operation Result: %#lf\n",timestamps[7]-timestamps[6], h_out );

   //------------------------------------------------------------------- DIVISION
    a_inp = ((double)rand())/((double)(RAND_MAX/DEC_PLC));
    b_inp = ((double)rand())/((double)(RAND_MAX/DEC_PLC));

   //Software x 5
   timestamps[0] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
   }
   timestamps[1] = get_UTC_time();

   //Hardware x 5
   timestamps[2] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
   }
   timestamps[3] = get_UTC_time();

   //Software x 10
   timestamps[4] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
      s_out = bare_division(a_inp, b_inp);
   }
   timestamps[5] = get_UTC_time();

   //Hardware x 10
   timestamps[6] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
      h_out = a_inp / b_inp;
   }
   timestamps[7] = get_UTC_time();

   printf("\nFor %ld interations: DIVISION\n",ITR_NUM );
   printf("x5  :\n");
   printf("   Software : %ld cycles, Operation Result: %#lf\n",timestamps[1]-timestamps[0], s_out );
   printf("   Hardware : %ld cycles, Operation Result: %#lf\n",timestamps[3]-timestamps[2], h_out );
   printf("x10 :\n");
   printf("   Software : %ld cycles, Operation Result: %#lf\n",timestamps[5]-timestamps[4], s_out );
   printf("   Hardware : %ld cycles, Operation Result: %#lf\n",timestamps[7]-timestamps[6], h_out );



   //------------------------------------------------------------------- MULTIPLICATION 
    a_inp = ((double)rand())/((double)(RAND_MAX/DEC_PLC));
    b_inp = ((double)rand())/((double)(RAND_MAX/DEC_PLC));

   //Software x 5
   timestamps[0] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
   }
   timestamps[1] = get_UTC_time();

   //Hardware x 5
   timestamps[2] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
   }
   timestamps[3] = get_UTC_time();

   //Software x 10
   timestamps[4] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
      s_out = bare_multiply(a_inp, b_inp);
   }
   timestamps[5] = get_UTC_time();

   //Hardware x 10
   timestamps[6] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
      h_out = a_inp * b_inp;
   }
   timestamps[7] = get_UTC_time();

   printf("\nFor %ld interations: MULTIPLY\n",ITR_NUM );
   printf("x5  :\n");
   printf("   Software : %ld cycles, Operation Result: %#lf\n",timestamps[1]-timestamps[0], s_out );
   printf("   Hardware : %ld cycles, Operation Result: %#lf\n",timestamps[3]-timestamps[2], h_out );
   printf("x10 :\n");
   printf("   Software : %ld cycles, Operation Result: %#lf\n",timestamps[5]-timestamps[4], s_out );
   printf("   Hardware : %ld cycles, Operation Result: %#lf\n",timestamps[7]-timestamps[6], h_out );


   //------------------------------------------------------------------- SQUARE ROOT 
    a_inp = ((double)rand())/((double)(RAND_MAX/DEC_PLC));
    b_inp = ((double)rand())/((double)(RAND_MAX/DEC_PLC));

   //Software x 5
   timestamps[0] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
   }
   timestamps[1] = get_UTC_time();

   //Hardware x 5
   timestamps[2] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
      h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
   }
   timestamps[3] = get_UTC_time();

   //Software x 10
   timestamps[4] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
       s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
     s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
      s_out = bare_sqrt(a_inp);
   }
   timestamps[5] = get_UTC_time();

   //Hardware x 10
   timestamps[6] = get_UTC_time();
   for(i=0; i < ITR_NUM; ++i){
       h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
    h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
      h_out =sqrt( a_inp) ;
   }
   timestamps[7] = get_UTC_time();

   printf("\nFor %ld interations: SQRT\n",ITR_NUM );
   printf("x5  :\n");
   printf("   Software : %ld cycles, Operation Result: %#lf\n",timestamps[1]-timestamps[0], s_out );
   printf("   Hardware : %ld cycles, Operation Result: %#lf\n",timestamps[3]-timestamps[2], h_out );
   printf("x10 :\n");
   printf("   Software : %ld cycles, Operation Result: %#lf\n",timestamps[5]-timestamps[4], s_out );
   printf("   Hardware : %ld cycles, Operation Result: %#lf\n",timestamps[7]-timestamps[6], h_out );

   /*
      printf("Add_result  : %#lf\n\n", bare_add(-5,5) );
      printf("Add_result  : %#lf\n\n", bare_add(5,-5) );
      printf("Add_result  : %#lf\n\n", bare_add(-0.725,11.9) );
      printf("Add_result  : %#lf\n\n", bare_add(0.725,-11.9) );
      printf("Add_result  : %#lf\n\n", bare_add(1.625,-2) );
      printf("Add_result  : %#lf\n\n", bare_add(-1.625,2) );
      printf("Add_result  : %#lf\n\n", bare_add(-7,2) );
      printf("Add_result  : %#lf\n\n", bare_add(7,-2) );

      printf("Add_result  : %#lf\n\n", bare_add(7,2) );
      printf("Add_result  : %#lf\n\n", bare_add(17,5) );
      printf("Add_result  : %#lf\n\n", bare_add(5,1.414) );
      printf("Add_result  : %#lf\n\n", bare_add(2,1.414) );
      printf("Add_result  : %#lf\n\n", bare_add(2.414,1) );

      printf("Add_result  : %#lf\n\n", bare_add(2,7) );
      printf("Add_result  : %#lf\n\n", bare_add(5,17) );
      printf("Add_result  : %#lf\n\n", bare_add(1.414,5) );
      printf("Add_result  : %#lf\n\n", bare_add(1.414,2) );
      printf("Add_result  : %#lf\n\n", bare_add(1,2.414) );

      printf("Add_result  : %#lf\n\n", bare_add(1,1) );
      printf("Add_result  : %#lf\n\n", bare_add(5.2,5.1) );
      printf("Add_result  : %#lf\n\n", bare_add(5.1,5.2) );

      printf("Sub_result : %#lf\n\n", bare_subtract(-5,5) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(5,-5) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(-0.725,11.9) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(1.625,-2) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(-7,2) );

      printf("Sub_result  : %#lf\n\n", bare_subtract(7,2) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(17,5) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(5,1.414) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(2,1.414) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(2.414,1) );

      printf("Sub_result  : %#lf\n\n", bare_subtract(2,7) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(5,17) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(1.414,5) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(1.414,2) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(1,2.414) );

      printf("Sub_result  : %#lf\n\n", bare_subtract(1,1) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(5.2,5.1) );
      printf("Sub_result  : %#lf\n\n", bare_subtract(5.1,5.2) );

      printf("Mult_result : %#lf\n\n", bare_multiply(-5,5) );
      printf("Mult_result : %#lf\n\n", bare_multiply(5,-5) );
      printf("Mult_result : %#lf\n\n", bare_multiply(-0.725,11.9) );
      printf("Mult_result : %#lf\n\n", bare_multiply(1.625,-2) );
      printf("Mult_result : %#lf\n\n", bare_multiply(-7,2) );
      printf("Mult_result : %#lf\n\n", bare_multiply(7,2) );
      printf("Mult_result : %#lf\n\n", bare_multiply(17,5) );
      printf("Mult_result : %#lf\n\n", bare_multiply(5,1.414) );
      printf("Mult_result : %#lf\n\n", bare_multiply(2,1.414) );

      printf("Divs_result : %#lf\n\n", bare_division(-5,5) );
      printf("Divs_result : %#lf\n\n", bare_division(5,-5) );
      printf("Divs_result : %#lf\n\n", bare_division(-0.725,11.9) );
      printf("Divs_result : %#lf\n\n", bare_division(1.625,-2) );
      printf("Divs_result : %#lf\n\n", bare_division(-7,2) );
      printf("Divs_result : %#lf\n\n", bare_division(7,2) );
      printf("Divs_result : %#lf\n\n", bare_division(17,5) );
      printf("Divs_result : %#lf\n\n", bare_division(5,1.414) );
      printf("Divs_result : %#lf\n\n", bare_division(2,1.414) );

      printf("Sqrt_result : %#lf\n\n", bare_sqrt(1000000000000) );
      printf("Sqrt_result : %#lf\n\n", bare_sqrt(1000000) );
      printf("Sqrt_result : %#lf\n\n", bare_sqrt(400) );
   printf("Sqrt_result : %#lf\n\n", bare_sqrt(144) );
   printf("Sqrt_result : %#lf\n\n", bare_sqrt(169) );
   printf("Sqrt_result : %#lf\n\n", bare_sqrt(25) );
   printf("Sqrt_result : %#lf\n\n", bare_sqrt(5) );
   printf("Sqrt_result : %#lf\n\n", bare_sqrt(2) );
   */

      printf("\n\n_____________________________ PART III : THE UNION _______________________________\n\n");
   union rawr b;
   b.dval = -7588933081.61803398875; 

   uint64_t dval, dval_sign, dval_expo ;
   double   dval_frac;
   __bare_parse(b.dval, &dval, &dval_sign, &dval_expo,(uint64_t*) &dval_frac);
   dval_frac = bare_frexp(b.dval,(int*) &dval_expo);
   printf("\nDouble   : %#lf\n", b.dval);
   printf("Sign     : %#ld\n", dval_sign);
   printf("Exponent : %#ld\n", dval_expo);
   printf("Mantissa : %#lf\n\n", dval_frac);


   printf("Long     : %#ld\n", b.lval);
   printf("Sign     : %#ld\n\n", (((b.lval>>30)>>30)>>3) & 0x1  );

   printf("Character: \"");
   for(uint8_t i = 0; i < 8; ++i)
      printf("%c",b.cval[i]);
   printf("\"\n");
   printf("\n\n___________________________________ THE END ______________________________________\n\n");

   return 0;
}
