#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(){
    /*I declared some variables and pointers for arrays*/
	int xs,seqlen,looplen,*h,*loop,*seq;
    int i=0;
    /*I create an array for loop using malloc*/
    loop=(int*)malloc(100 * sizeof(int));

    /*I create an array for histogram using malloc*/
    h=(int*)malloc(9 * sizeof(int));
   
    /*I get the length and first term of the array from the user.*/
    printf("Please enter the sequence length: ");
    scanf("%d",&seqlen);
    printf("Please enter the first element: ");
    scanf("%d",&xs);

    /*I called the check_loop_iterative function and printed the results.*/    
    looplen = seqlen;
    check_loop_iterative(generate_sequence,xs,seqlen,loop,&looplen);
    if(looplen != 0){
        printf("Loop: {%d",loop[0]);
        while(looplen != 1){
            printf(",%d",loop[i+1]);
            i++;
            looplen--;
        }
        printf("}\n\n");
    }

    /*Creating histogram*/
    hist_of_firstdigits(generate_sequence, xs, seqlen, h, 1);
    
    printf("Histogram of the sequence: {%d",h[0]);
    
    /*Printing histogram*/
    for(int i = 1;i<9;i++){
        printf(",%d",h[i]);
    }
    printf("}\n");

    /* Deallocate allocated memory */
    free(loop);
    free(h);
}

