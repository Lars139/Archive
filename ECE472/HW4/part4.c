#include <stdio.h>
#include "part4.h"

/* Func: det_endianess(void)
 * Desc: The function will determine if the system is big or small endianess
 * Output:
 *  The short value should be 
 *   0x007F if BIG_ENDIAN
 *   0x7F00 if SML_ENDIAN
 */
short det_endianess(void){
   short meta_end_val;
   char *meta_end_ptr;
   meta_end_ptr = (char *) &meta_end_val;

   meta_end_ptr[0] = 0x00;
   meta_end_ptr[1] = 0x7F;

   return meta_end_val;
}


void part4(void){
   short part4_endianess;
   short val;
   char *p_val;
   p_val = (char *) &val;

   part4_endianess = det_endianess();

   if(0x007F == part4_endianess){ //Small Endianess
      printf("__BIG_ENDIAN__\n");
      p_val[0] = 0x12;
      p_val[1] = 0x34;
   }else if(0x7F00 == part4_endianess){//Big Endianess
      printf("__LITTLE_ENDIAN__\n");
      p_val[1] = 0x12;
      p_val[0] = 0x34;
   }

   printf("Part4: %x\n", val);

   return;
}
