#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "leaf1.c"
#include "leaf2.c"
#include "leaf4.c"

int main(int argc, char **argv)
{
   uint32_t MAX_LEAF;

   unsigned int eax;
   unsigned int ebx;
   unsigned int ecx;
   unsigned int edx;

   char vendor[13];
   uint32_t buff;
   uint32_t buff1;
   uint32_t buff2;

   //#############################  EAX = 00 ################################
   //Original code -- printing out vendor
   printf("\n[EAX=00: Vendor and Highest Number of Leaf]\n"); 
   eax = 0x00;
   __asm__ __volatile__(
	 "cpuid;"
	 : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	 : "a"(eax)
	 );
   memcpy(vendor, (char*)&ebx, 4);
   memcpy(vendor + 4, (char*)&edx, 4);
   memcpy(vendor + 8, (char*)&ecx, 4);
   vendor[12] = 0;
   printf(" %s\n", vendor);
   printf(" Highest Number of Leaf: %i\n",eax);
   MAX_LEAF = eax;

   //#########################  EAX = 80000000 ##############################
   //---------------------------------------------------  Processor Type
   //See pg.701
   printf("\n[EAX=0x80000000: Processor Type]\n"); 
   eax = 0x80000000;
   __asm__ __volatile__(
	 "cpuid;"
	 : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	 : "a"(eax)
	 );
   buff = eax & 0x3;
   switch (buff){
      case 0b00:
	 printf(" Original OEM Processor\n");
	 break;
      case 0b01:
	 printf(" Intel OverDrive Processor\n");
	 break;
      case 0b10:
	 printf(" Dual Porcessor (N/A to Intel486 Processors)\n");
	 break;
      case 0b11:
	 printf(" Intel Reserved\n");
	 break;
   }

   //-------------------------------------------------  Processor Brand
   //-------------------------------------------------  CPU name 
   //See pg.713
   printf("\n[EAX=0x80000002: Processor Brand]\n"); 
   if(eax >= 0x80000002){
      uint32_t temp = 0x80000002;
      for(int i = 0; i<3; i++){	 
	 eax = temp;
	 __asm__ __volatile__(
	       "cpuid;"
	       : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	       : "a"(eax)
	       );
	 for(int j = 0; j<4; ++j){
	    printf("%c", (eax & 0xFF<<j*8)>>j*8);
	 }
	 for(int j = 0; j<4; ++j){
	    printf("%c", (ebx & 0xFF<<j*8)>>j*8);
	 }
	 for(int j = 0; j<4; ++j){
	    printf("%c", (ecx & 0xFF<<j*8)>>j*8);
	 }
	 for(int j = 0; j<4; ++j){
	    printf("%c", (edx & 0xFF<<j*8)>>j*8);
	 }
	 temp++;
      }
      printf("\n");
   }else{
      printf("\n[EAX=0x80000002: Processor Brand: Not Supported]\n"); 
   }


   //#########################  EAX = 80000008 ##############################
   //See pg.699
   //--------------------------------------  Physical address width
   //--------------------------------------  Logical address width
   printf("\n[EAX=0x80000008: Address Width]\n"); 
   eax = 0x80000008;
   __asm__ __volatile__(
	 "cpuid;"
	 : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	 : "a"(eax)
	 );
   printf(" Physical Address Bits: %i\n", eax & 0xFF);
   printf(" Linear Address Bits: %i\n", (eax & (0xFF<<8))>>8);


   //#############################  EAX = 01 ################################
   //-------------------------------------------------- CPU family
   //See pg.700 vol 2
   if(MAX_LEAF >= 1){
      printf("\n[EAX=01: CPU Info]\n"); 
      eax = 0x01;
      buff2=0;
      __asm__ __volatile__(
	    "cpuid;"
	    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	    : "a"(eax)
	    );
      buff = (eax & 0xF);
      printf(" Stepping ID: %i\n",buff);

      //Family Display
      buff = (eax & 0xF00)>>8;
      if(buff == 0x0F)
	 printf(" Family ID: %x\n",buff);
      else{
	 buff1 = (eax & 0xFF00000)>>20;
	 printf(" Family ID: %x\n",buff1+buff);
      }

      //--------------------------------------------   CPU model (number and name)
      //Model Display
      buff1 = (eax & 0xF<<4)>>4;
      if(buff == 0x06 || buff == 0x0F){
	 buff2 = (eax & 0xF<<16)>>16;
	 printf(" Model: %x\n",(buff2<<4)+buff1);
      }else{
	 printf(" Model: %x\n",buff1);
      }

      //------------------------------------------   CPU features available
      printf(" Features: \n");
      disp_CPUID_leaf1_ecx(ecx);
      disp_CPUID_leaf1_edx(edx);
      printf("\n");
   }

   //#############################  EAX = 02 ################################
   //See pg.709 vol 2
   if(MAX_LEAF >= 2 ){
      eax = 0x02;
      __asm__ __volatile__(
	    "cpuid;"
	    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	    : "a"(eax)
	    );
      //------------------------------------   TLB information (any and all)
      printf("\n[EAX=02: TLB]\n"); 
      printf("EAX\n"); 
      if( ~eax & (1<<31) )
	 for(int i=1; i<4; ++i){
	    disp_CPUID_leaf2( eax & (0xF<<(i*4)) );
	 }

      printf("\nEBX\n"); 
      if( ~ebx & (1<<31) )
	 for(int i=0; i<4; ++i){
	    disp_CPUID_leaf2( ebx & (0xF<<(i*4)) );
	 }

      printf("\nECX\n"); 
      if( ~ecx & (1<<31) )
	 for(int i=0; i<4; ++i){
	    disp_CPUID_leaf2( ecx & (0xF<<(i*4)) );
	 }

      printf("\nEDX\n"); 
      if( ~edx & (1<<31) )
	 for(int i=0; i<4; ++i){
	    disp_CPUID_leaf2( edx & (0xF<<(i*4)) );
	 }
   }else{
      printf("\n[EAX=02: TLB: Not Supported]\n"); 
   }

   //#############################  EAX = 04 ################################
   //------------------------------  L1 instruction cache size (with line info)
   //-------------------------------------  L1 data cache size (with line info)
   //-------------------------------------  Memory hierarchy information
   //See pg.690 vol 2
   //See pg.710 vol 2
   if(MAX_LEAF >= 4){
      printf("\n[EAX=04: Caches]\n"); 
      for(int i = 0; i<32; ++i){
	 eax = 0x04;
	 ecx = i;
	 __asm__ __volatile__(
	       "cpuid;"
	       : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	       : "a"(eax), "c"(ecx)
	       );
	 //EAX is output see pg.690
	 disp_CPUID_leaf4( eax, ebx, ecx, edx);
      }

   //-------------------------------------  Number of Logical CPU 
      printf("\n[EAX=04: Logical CPU]\n"); 
	 eax = 0x04;
	 ecx = 0x0;
	 __asm__ __volatile__(
	       "cpuid;"
	       : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	       : "a"(eax), "c"(ecx)
	       );
	 printf(" Number of Logical CPU: %i\n", (eax>>26) + 1);

   }else{
      printf("\n[EAX=04: Caches: Not Supported]\n"); 
   }

   //#############################  EAX = 16 ################################
   //---------------------------------------------------------  CPU frequency 
   if(MAX_LEAF >=16){
      printf("\n[EAX=16: Processor Frequency]\n"); 
      eax = 0x16;
      __asm__ __volatile__(
	    "cpuid;"
	    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	    : "a"(eax), "c"(ecx)
	    );
      printf(" Base Frequency: %i MHz\n", eax & 0xFFFF);
      printf(" Max Frequency: %i MHz\n", ebx & 0xFFFF);
      printf(" Bus Frequency: %i MHz\n", ecx & 0xFFFF);
   }else{
      printf("\n[EAX=16: Processor Frequency: Not Supported]\n");
   }
   //   number of logical CPUs (Not support)
   return 0;
}
