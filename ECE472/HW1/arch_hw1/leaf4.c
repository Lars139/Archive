/* Author: Rattanai Sawaspanich
 * Date: Oct 11,2015
 * File: leaf4.c
 */

/* Func: disp_CPUID_leaf4()
 * Input: EAX, EBX, ECX, EDX
 * Desc: Take EAX, EBX, ECX, EDX from calling CPUID and
 *       decipher cache/memory heirachy information
 */

void disp_CPUID_leaf4(uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx){
   uint32_t l4_buff;
   l4_buff = eax & 0x1F;
   //Caches?
   if( l4_buff ){
      //Displaying type of cache (if any)
      switch (l4_buff){
	 case 1:
	    printf(" Data Cache ");
	    break;

	 case 2:
	    printf(" Instruction Cache ");
	    break;

	 case 3:
	    printf(" Unified Cache ");
	    break;

	 default:
	    printf(" Reserved bit");
	    break;
      }

      //Cache Level
      l4_buff = (eax & 0x7<<5) >> 5;
      printf("L%i, ",l4_buff);

      //Self Init cache lvl
      l4_buff = eax & 0x1<<8;
      if(l4_buff)
      printf("Self Intialized, ");

      //Fully Associative cache
      l4_buff = eax & 0x1<<9;
      if(l4_buff)
      printf("Fully Associative, ");

      //Caceh size
      l4_buff = ((ebx & 0x3FF<<22) + 1) * ((ebx & 0x3FF<<12) + 1) * ((ebx & 0x7FF) + 1) * (ecx + 1);
      printf("%i Bytes ",l4_buff);

      printf("\n");
   }else
      return;
   return ;
}
