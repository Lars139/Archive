/* Author: Rattanai Sawaspanich
 * Date  : Oct 10,2015
 * File  : leaf1.c
 */

/* Func  : disp_CPUID_leaf1_ecx
 * Desc  : The func decipher the available features from CPUID via ECX
 * Input : a return ECX register from CPUID with EAX=1
 */
void disp_CPUID_leaf1_ecx(uint32_t ecx){
   if(ecx & (1<<0))
      printf(" SSE3 ");
   if(ecx & (1<<1))
      printf(" PCLMULQDQ ");
   if(ecx & (1<<2))
      printf(" DTES64 ");
   if(ecx & (1<<3))
      printf(" MONITOR ");
   if(ecx & (1<<4))
      printf(" DS-CPL ");
   if(ecx & (1<<5))
      printf(" VMX ");
   if(ecx & (1<<6))
      printf(" SMX ");
   if(ecx & (1<<7))
      printf(" EIST ");
   if(ecx & (1<<8))
      printf(" TM2 ");
   if(ecx & (1<<9))
      printf(" SSSE3 ");
   if(ecx & (1<<10))
      printf(" CNXT-ID ");
   if(ecx & (1<<11))
      printf(" SDBG ");
   if(ecx & (1<<12))
      printf(" FMA ");
   if(ecx & (1<<13))
      printf(" CMPXCHG16B ");
   if(ecx & (1<<14))
      printf(" xTPR ");
   if(ecx & (1<<15))
      printf(" PDCM ");
   if(ecx & (1<<17))
      printf(" PCID ");
   if(ecx & (1<<18))
      printf(" DCA ");
   if(ecx & (1<<19))
      printf(" SSE4_1 ");
   if(ecx & (1<<20))
      printf(" SSE4_2 ");
   if(ecx & (1<<21))
      printf(" x2APIC ");
   if(ecx & (1<<22))
      printf(" MOVBE ");
   if(ecx & (1<<23))
      printf(" POPCNT ");
   if(ecx & (1<<24))
      printf(" TSC-Deadline ");
   if(ecx & (1<<25))
      printf(" AES ");
   if(ecx & (1<<26))
      printf(" XSAVE ");
   if(ecx & (1<<27))
      printf(" OSXSAVE ");
   if(ecx & (1<<28))
      printf(" AVX ");
   if(ecx & (1<<29))
      printf(" F16C ");
   if(ecx & (1<<30))
      printf(" RDRAND ");
}

/* Func  : disp_CPUID_leaf1_edx
 * Desc  : The func decipher the available features from CPUID via ECX
 * Input : a return EDX register from CPUID with EAX=1
 */
void disp_CPUID_leaf1_edx(uint32_t edx){
   if(edx & (1<<0))
      printf(" FPU ");
   if(edx & (1<<1))
      printf(" VME ");
   if(edx & (1<<2))
      printf(" DE ");
   if(edx & (1<<3))
      printf(" PSE ");
   if(edx & (1<<4))
      printf(" TSC ");
   if(edx & (1<<5))
      printf(" MSR ");
   if(edx & (1<<6))
      printf(" PAE ");
   if(edx & (1<<7))
      printf(" MCE ");
   if(edx & (1<<8))
      printf(" CX8 ");
   if(edx & (1<<9))
      printf(" APIC ");
   if(edx & (1<<11))
      printf(" SEP ");
   if(edx & (1<<12))
      printf(" MTRR ");
   if(edx & (1<<13))
      printf(" PGE ");
   if(edx & (1<<14))
      printf(" MCA ");
   if(edx & (1<<15))
      printf(" CMOV ");
   if(edx & (1<<16))
      printf(" PAT ");
   if(edx & (1<<17))
      printf(" PSE-36 ");
   if(edx & (1<<18))
      printf(" PSN ");
   if(edx & (1<<19))
      printf(" CLFSH ");
   if(edx & (1<<21))
      printf(" DS ");
   if(edx & (1<<22))
      printf(" ACPI ");
   if(edx & (1<<23))
      printf(" MMX ");
   if(edx & (1<<24))
      printf(" FXSR ");
   if(edx & (1<<25))
      printf(" SSE ");
   if(edx & (1<<26))
      printf(" SSE2 ");
   if(edx & (1<<27))
      printf(" SS ");
   if(edx & (1<<28))
      printf(" HTT ");
   if(edx & (1<<29))
      printf(" TM ");
   if(edx & (1<<31))
      printf(" PBE ");
}
