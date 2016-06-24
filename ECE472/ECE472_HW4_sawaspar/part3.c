#include<stdio.h>
#include<endian.h>

void part3(void){
   short val;
   char *p_val;
   p_val = (char *) &val;
   //Default to Big Endian
   p_val[1] = 0x12;
   p_val[0] = 0x34;

#ifdef __BYTE_ORDER__
   #if   (__BYTE__ORDER__ == __BIG_ENDIAN__)
   printf("__LITTLE_ENDIAN__\n");
   p_val[1] = 0x12;
   p_val[0] = 0x34;
   #elif (__BYTE__ORDER__ == __LITTLE_ENDIAN__)
   printf("__BIG_ENDIAN__\n");
   printf("Part3: %x\n", val);
   p_val[0] = 0x12;
   p_val[1] = 0x34;
   #else
      #error "UNKNOWN ENDIAN"
   #endif
#endif

   printf("Part3: %x\n", val);

   return;
}
