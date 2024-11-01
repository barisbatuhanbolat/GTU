#include <stdio.h>
#include <stdlib.h>
#include "util.h"
void generate_sequence(int xs, int currentlen, int seqlen, int *seq){
    int n;
    /*Termination condition*/
    if(seqlen == 0){
        return;
    }
    /*Collatz Conjecture rules for creating sequence*/
    if(xs%2 == 0){
        n = xs/2;
        seq[currentlen] = n;
    }
    else if(xs%2 != 0){
        n = 3*xs+1;
        seq[currentlen] = n;
    }

    generate_sequence(n,++currentlen,--seqlen,seq);
}
    
void check_loop_iterative(void (*f)(int,int,int,int *), int xs, int seqlen, int *loop, int *looplen){
    /*Declaring Variables*/
    int ni,ns,j,i,loop_length;
    static int *seq;
    /*This part will only run once as long as the program is running.*/
    if(*looplen == seqlen){
        /*Creating array with malloc*/
        seq=(int*)malloc(seqlen* sizeof(int));
        /*Fill array by using generate_sequence function */ 
        seq[0] = xs;
        (*f)(xs,1,seqlen,seq);
        /*Printing sequence*/
        printf("\nSequence: {");
        printf("%d",seq[0]);
        for(i=1;i<seqlen;i++){
            printf(",%d",seq[i]);
        }
        printf("}\n\n");
        xs = seqlen/2;
    }
    
    printf("Checking if there is a loop of length %d...\n",seqlen-xs-1);

    /*Succesfull Termination condition*/
    if(loop[40] == 1){
        ni = loop[0];
        ns = loop[1];
        printf("\n\nLoop detected with a length of %d\n",seqlen-xs-1);
        *looplen = ns-ni;
        for(i=ni,j=0;i<ns;i++,j++){
            loop[j] = seq[i];
        }
        free(seq);
        printf("The indexes of the loop's first occurance: %d(First Digit) , %d(Last Digit)\n",ni,ns);
        return;
    }
    /*Failed Termination condition*/
    if(seqlen-xs-1 == 0 && loop[40] == 0){
        printf("No loop found\n");
        *looplen = 0;
        free(seq);
        return;
    }

    (*looplen)--;
    loop[40] = has_loop(seq, xs, seqlen, &loop[0], &loop[1]);
    check_loop_iterative(generate_sequence,++xs,seqlen,loop,looplen);
}
int has_loop(int *arr, int n, int looplen, int *ls, int *le){
    /*Quick termination for has_loop function*/
    if(arr[looplen-1] == 1){
        for(int i = 0;i<looplen;i++){
            if(arr[i] == 4){
                *ls = i;
                *le = i+3;
                return 1;
            }       
        }
    }

    else if(n != looplen-3){
        if(arr[n] == arr[looplen-3] && arr[n+1] == arr[looplen-2] && arr[n+2] == arr[looplen-1]){
            for(int i = 0;i<looplen;i++){
                if(arr[n] == arr[i]){
                    *ls = i;
                    *le = looplen;
                    *le = *ls + (*le-*ls+1)/2 ;
                    return 1;
                }       
            }
        }
        else{
            return 0;
        }
    }
}
/*Fİnding first digits of every element of sequence*/
void first_digit(int *seq,int seqlen,int *temp){
    int first,i;
    for(i = 0;i<seqlen;i++){
        first = seq[i];
        while(first >= 10){
            first = first / 10;
        }
        temp[i] = first;
    }
}
void hist_of_firstdigits(void (*f)(int,int,int,int *), int xs, int seqlen, int *h, int digit){
    /*Declaration variables*/
    int i,temp[seqlen];
    static int *seq;
    /*Creating array with malloc*/
    seq=(int*)malloc(seqlen* sizeof(int));
    /*Fill array by using generate_sequence function */ 
    seq[0] = xs;
    (*f)(xs,1,seqlen,seq);
    first_digit(seq,seqlen,temp);

    if(digit>=1 && digit<=9){
        /*Fill array by using generate_sequence function */
        for(int i = 0;i<seqlen;i++){
            if(temp[i] == digit){
                h[digit-1]++;
            }
        }
        /*Termination condition*/
        if(digit == 9){
            return;
        }
    }
    /* Deallocate allocated memory */
    free(seq);
    hist_of_firstdigits(generate_sequence, xs, seqlen, h, ++digit);
}