/* Author: Rattanai Sawaspanich
 * Date  : Oct 10, 2015
 * 
 * Func  : disp_CPUID_leaf2
 * Input : an integer value
 * Desc  : The function decipher an int value obtained from CPUID leaf2
 */

void disp_CPUID_leaf2(uint32_t val){
   switch(val){
      case 0x01: printf( " Instruction    4 KByte pages, 4-way set associative, 32 entries\n");break;
      case 0x02: printf( " Instruction    4 MByte pages, fully associative, 2 entries\n");break;
      case 0x03: printf( " Data    4 KByte pages, 4-way set associative, 64 entries\n");break;
      case 0x04: printf( " Data    4 MByte pages, 4-way set associative, 8 entries\n");break;
      case 0x05: printf( " Data  1  4 MByte pages, 4-way set associative, 32 entries\n");break;
      case 0x06: printf( " 1st-level instruction cache  8 KBytes, 4-way set associative, 32 byte line size\n");break;
      case 0x08: printf( " 1st-level instruction cache  16 KBytes, 4-way set associative, 32 byte line size\n");break;
      case 0x09: printf( " 1st-level instruction cache  32KBytes, 4-way set associative, 64 byte line size\n");break;
      case 0x0A: printf( " 1st-level data cache  8 KBytes, 2-way set associative, 32 byte line size\n");break;
      case 0x0B: printf( " Instruction TLB: 4 MByte pages, 4-way set associative, 4 entries\n");break;
      case 0x0C: printf( " 1st-level data cache  16 KBytes, 4-way set associative, 32 byte line size\n");break;
      case 0x0D: printf( " 1st-level data cache  16 KBytes, 4-way set associative, 64 byte line size\n");break;
      case 0x0E: printf( " 1st-level data cache  24 KBytes, 6-way set associative, 64 byte line size\n");break;
      case 0x1D: printf( " 2nd-level cache  128 KBytes, 2-way set associative, 64 byte line size\n");break;
      case 0x21: printf( " 2nd-level cache  256 KBytes, 8-way set associative, 64 byte line size\n");break;
      case 0x22: printf( " 3rd-level cache  512 KBytes, 4-way set associative, 64 byte line size, 2 lines per sector\n");break;
      case 0x23: printf( " 3rd-level cache  1 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector\n");break;
      case 0x24: printf( " 2nd-level cache  1 MBytes, 16-way set associative, 64 byte line size\n");break;
      case 0x25: printf( " 3rd-level cache  2 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector\n");break;
      case 0x29: printf( " 3rd-level cache  4 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector\n");break;
      case 0x2C: printf( " 1st-level data cache  32 KBytes, 8-way set associative, 64 byte line size\n");break;
      case 0x30: printf( " 1st-level instruction cache  32 KBytes, 8-way set associative, 64 byte line size\n");break;
      case 0x40: printf( " No 2nd-level cache or, if processor contains a valid 2nd-level cache, no 3rd-level cache\n");break;
      case 0x41: printf( " 2nd-level cache  128 KBytes, 4-way set associative, 32 byte line size\n");break;
      case 0x42: printf( " 2nd-level cache  256 KBytes, 4-way set associative, 32 byte line size\n");break;
      case 0x43: printf( " 2nd-level cache  512 KBytes, 4-way set associative, 32 byte line size\n");break;
      case 0x44: printf( " 2nd-level cache  1 MByte, 4-way set associative, 32 byte line size\n");break;
      case 0x45: printf( " 2nd-level cache  2 MByte, 4-way set associative, 32 byte line size\n");break;
      case 0x46: printf( " 3rd-level cache  4 MByte, 4-way set associative, 64 byte line size\n");break;
      case 0x47: printf( " 3rd-level cache  8 MByte, 8-way set associative, 64 byte line size\n");break;
      case 0x48: printf( " 2nd-level cache  3MByte, 12-way set associative, 64 byte line size\n");break;
      case 0x49: printf( " 3rd-level cache  4MB, 16-way set associative, 64-byte line size (Intel Xeon processor MP, Family 0FH, Model 06H); \n2nd-level cache 4 MByte, 16-way set associative, 64 byte line size\n");break;
      case 0x4A: printf( " 3rd-level cache  6MByte, 12-way set associative, 64 byte line size\n");break;
      case 0x4B: printf( " 3rd-level cache  8MByte, 16-way set associative, 64 byte line size\n");break;
      case 0x4C: printf( " 3rd-level cache  12MByte, 12-way set associative, 64 byte line size\n");break;
      case 0x4D: printf( " 3rd-level cache  16MByte, 16-way set associative, 64 byte line size\n");break;
      case 0x4E: printf( " 2nd-level cache  6MByte, 24-way set associative, 64 byte line size\n");break;
      case 0x4F: printf( " Instruction    4 KByte pages, 32 entries\n");break;
      case 0x50: printf( " Instruction    4 KByte and 2-MByte or 4-MByte pages, 64 entries\n");break;
      case 0x51: printf( " Instruction    4 KByte and 2-MByte or 4-MByte pages, 128 entries\n");break;
      case 0x52: printf( " Instruction    4 KByte and 2-MByte or 4-MByte pages, 256 entries\n");break;
      case 0x55: printf( " Instruction    2-MByte or 4-MByte pages, fully associative, 7 entries\n");break;
      case 0x56: printf( " Data  0  4 MByte pages, 4-way set associative, 16 entries\n");break;
      case 0x57: printf( " Data  0  4 KByte pages, 4-way associative, 16 entries\n");break;
      case 0x59: printf( " Data  0  4 KByte pages, fully associative, 16 entries\n");break;
      case 0x5A: printf( " Data  0  2-MByte or 4 MByte pages, 4-way set associative, 32 entries\n");break;
      case 0x5B: printf( " Data    4 KByte and 4 MByte pages, 64 entries\n");break;
      case 0x5C: printf( " Data    4 KByte and 4 MByte pages,128 entries\n");break;
      case 0x5D: printf( " Data    4 KByte and 4 MByte pages,256 entries\n");break;
      case 0x60: printf( " 1st-level data cache  16 KByte, 8-way set associative, 64 byte line size\n");break;
      case 0x61: printf( " Instruction    4 KByte pages, fully associative, 48 entries\n");break;
      case 0x63: printf( " Data    1 GByte pages, 4-way set associative, 4 entries \n");break;
      case 0x66: printf( " 1st-level data cache  8 KByte, 4-way set associative, 64 byte line size\n");break;
      case 0x67: printf( " 1st-level data cache  16 KByte, 4-way set associative, 64 byte line size\n");break;
      case 0x68: printf( " 1st-level data cache  32 KByte, 4-way set associative, 64 byte line size\n");break;
      case 0x70: printf( " Trace cache  12 K-?op, 8-way set associative\n");break;
      case 0x71: printf( " Trace cache  16 K-?op, 8-way set associative\n");break;
      case 0x72: printf( " Trace cache  32 K-?op, 8-way set associative\n");break;
      case 0x76: printf( " Instruction    2M/4M pages, fully associative, 8 entries\n");break;
      case 0x78: printf( " 2nd-level cache  1 MByte, 4-way set associative, 64byte line size\n");break;
      case 0x79: printf( " 2nd-level cache  128 KByte, 8-way set associative, 64 byte line size, 2 lines per sector\n");break;
      case 0x7A: printf( " 2nd-level cache  256 KByte, 8-way set associative, 64 byte line size, 2 lines per sector\n");break;
      case 0x7B: printf( " 2nd-level cache  512 KByte, 8-way set associative, 64 byte line size, 2 lines per sector\n");break;
      case 0x7C: printf( " 2nd-level cache  1 MByte, 8-way set associative, 64 byte line size, 2 lines per sector\n");break;
      case 0x7D: printf( " 2nd-level cache  2 MByte, 8-way set associative, 64byte line size\n");break;
      case 0x7F: printf( " 2nd-level cache  512 KByte, 2-way set associative, 64-byte line size\n");break;
      case 0x80: printf( " 2nd-level cache  512 KByte, 8-way set associative, 64-byte line size\n");break;
      case 0x82: printf( " 2nd-level cache  256 KByte, 8-way set associative, 32 byte line size\n");break;
      case 0x83: printf( " 2nd-level cache  512 KByte, 8-way set associative, 32 byte line size\n");break;
      case 0x84: printf( " 2nd-level cache  1 MByte, 8-way set associative, 32 byte line size\n");break;
      case 0x85: printf( " 2nd-level cache  2 MByte, 8-way set associative, 32 byte line size\n");break;
      case 0x86: printf( " 2nd-level cache  512 KByte, 4-way set associative, 64 byte line size\n");break;
      case 0x87: printf( " 2nd-level cache  1 MByte, 8-way set associative, 64 byte line size\n");break;
      case 0xA0: printf( " DTLB   4k pages, fully associative, 32 entries\n");break;
      case 0xB0: printf( " Instruction    4 KByte pages, 4-way set associative, 128 entries\n");break;
      case 0xB1: printf( " Instruction    2M pages, 4-way, 8 entries or 4M pages, 4-way, 4 entries\n");break;
      case 0xB2: printf( " Instruction    4KByte pages, 4-way set associative, 64 entries\n");break;
      case 0xB3: printf( " Data    4 KByte pages, 4-way set associative, 128 entries\n");break;
      case 0xB4: printf( " Data  1  4 KByte pages, 4-way associative, 256 entries\n");break;
      case 0xB5: printf( " Instruction    4KByte pages, 8-way set associative, 64 entries\n");break;
      case 0xB6: printf( " Instruction    4KByte pages, 8-way set associative, 128 entries\n");break;
      case 0xBA: printf( " Data  1  4 KByte pages, 4-way associative, 64 entries\n");break;
      case 0xC0: printf( " Data    4 KByte and 4 MByte pages, 4-way associative, 8 entries\n");break;
      case 0xC1: printf( " Shared 2nd-Level    4 KByte/2MByte pages, 8-way associative, 1024 entries\n");break;
      case 0xC2: printf( " DTLB   4 KByte/2 MByte pages, 4-way associative, 16 entries\n");break;
      case 0xC3: printf( " Shared 2nd-Level    4 KByte /2 MByte pages, 6-way associative, 1536 entries.Also 1GBbyte pages, 4-way, 16 entries.\n");break;
      case 0xCA: printf( " Shared 2nd-Level    4 KByte pages, 4-way associative, 512 entries\n");break;
      case 0xD0: printf( " 3rd-level cache  512 KByte, 4-way set associative, 64 byte line size\n");break;
      case 0xD1: printf( " 3rd-level cache  1 MByte, 4-way set associative, 64 byte line size\n");break;
      case 0xD2: printf( " 3rd-level cache  2 MByte, 4-way set associative, 64 byte line size\n");break;
      case 0xD6: printf( " 3rd-level cache  1 MByte, 8-way set associative, 64 byte line size\n");break;
      case 0xD7: printf( " 3rd-level cache  2 MByte, 8-way set associative, 64 byte line size\n");break;
      case 0xD8: printf( " 3rd-level cache  4 MByte, 8-way set associative, 64 byte line size\n");break;
      case 0xDC: printf( " 3rd-level cache  1.5 MByte, 12-way set associative, 64 byte line size\n");break;
      case 0xDD: printf( " 3rd-level cache  3 MByte, 12-way set associative, 64 byte line size\n");break;
      case 0xDE: printf( " 3rd-level cache  6 MByte, 12-way set associative, 64 byte line size\n");break;
      case 0xE2: printf( " 3rd-level cache  2 MByte, 16-way set associative, 64 byte line size\n");break;
      case 0xE3: printf( " 3rd-level cache  4 MByte, 16-way set associative, 64 byte line size\n");break;
      case 0xE4: printf( " 3rd-level cache  8 MByte, 16-way set associative, 64 byte line size\n");break;
      case 0xEA: printf( " 3rd-level cache  12MByte, 24-way set associative, 64 byte line size\n");break;
      case 0xEB: printf( " 3rd-level cache  18MByte, 24-way set associative, 64 byte line size\n");break;
      case 0xEC: printf( " 3rd-level cache  24MByte, 24-way set associative, 64 byte line size\n");break;
      case 0xF0: printf( " 64-Byte prefetching\n");break;
      case 0xF1: printf( " 128-Byte prefetching\n");break;
      case 0xFF: printf( " CPUID leaf 2 does not report cache descriptor information, use CPUID leaf 4 to query cache parameters\n");break;
   }
}
