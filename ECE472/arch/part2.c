#include <stdio.h>
#include <stdlib.h>
#include "part2.h"

uint64_t get_CPU_UTC(){
   uint32_t eax;
   uint32_t edx;
   __asm__ __volatile__("RDTSC;"
	 :"=a"(eax), "=d"(edx)
	 );
   return ((uint64_t)eax) | ((uint64_t)edx << 32);
}

struct blob {
   struct blob *next;
   long padding[31]; 	//To make a blob size of 256 bytes
};


/*PSUEDO-CODE
 * 0) Define struct  -- 128-byte struct (NPAD = 31, ptr = 1)
 *
 * 1) Allocate array of struct
 * 2) Link the struct pointer
 * 3) Traverse the list say.. 100 times, Measure clk cycle it takes
 * 4) Find avg. time
 * 
 * 5) repeat (1) - (4) with different array size
 */
void part2(void){
   uint64_t t_start;
   uint64_t t_end;
   uint64_t t_delta;
   uint64_t blob_size;

   struct blob *cur_blob;

   printf("Blob size: %li bytes\n",blob_size = sizeof(struct blob));

   /* Alloc blob_arr w/ the array capacity doubling every iteration
    * Link each of the blob together with next ptr
    * Starting at 1KB size arr ( 4*(2^0) = 4 --> 1 KB)
    * Ending at 1000KB = 1MB ( 4*(2^10) = 4096 --> 1000KB = 1MB)  
    * num_blob is also the number of blob contain in a given byte size
    * (4 blobs at 1KB, 4096 blobs at 1MB)
    */
   for(int num_blob = 4; num_blob < 33445533; num_blob *= 2){

      struct blob *blob_arr = malloc(sizeof(struct blob)*num_blob);
      cur_blob = blob_arr;

      //Iterate through and set the prt for the array to link
      for(int j=0; j<num_blob; ++j){
	 blob_arr[j].next = blob_arr+j+1;
      }
      blob_arr[num_blob - 1].next = NULL;

      //Traverseing the list for 1000 times
      for(int j=0; j<1000; ++j){
	 //Start timer
	 t_start = get_CPU_UTC();

	 //Traverse the list
	 while(cur_blob->next != NULL){
	    ++(cur_blob->padding[0]); 	//Force write
	    cur_blob = cur_blob->next;	//Force read and traverse
	 }
	 //Stop timer
	 t_end = get_CPU_UTC();
	 t_delta += t_end - t_start;

      }//End Here -- Traversing for 100 times

      printf("Cache Size: %8.0f KB; Latency: %8.3f us\n", (float)num_blob/4.0 , (float) t_delta/((float)num_blob));
      t_delta = 0;

      free(blob_arr);

   }//End Here -- blob size inc


   return ;
}
