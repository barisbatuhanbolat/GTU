			.data
Str1:			.asciiz "Enter row number: "
Str2:			.asciiz "Enter column number: "
Str3:           	.asciiz "Initial Board"
Str4:           	.asciiz "Final Board"
newline: 		.asciiz "\n"  # Newline character


			.text
Main:
			la $a0, Str1         # printf("Enter row number: ");
			li $v0, 4            # Syscall 4: Print string
			syscall		
				
			li $v0, 5	     # Syscall 5: Read integer
			syscall		     # scanf("%d",$s0);
			move $s0, $v0	     # s0 stores row number	
					
			la $a0, Str2	     # printf("Enter column number: ");
			li $v0, 4            # Syscall 4: Print string
			syscall		
				
			li $v0, 5	    # Syscall 5: Read integer
			syscall		    # scanf("%d",$s1);
			move $s1, $v0	    # s1 stores column number	
			
			jal createArray     # Creating init board

            		la $s3, 0($t2)      # Load $s3 to the base address of the init array
		    
            		li $v0, 4           # Syscall 4: Print string
            		la $a0, newline     # printf("\n");
            		syscall
            		la $a0, Str3        # printf("Initial Board");
			li $v0, 4           # Syscall 4: Print string
			syscall
            		li $v0, 4           # Syscall 4: Print string
            		la $a0, newline     # printf("\n");
            		syscall

            		la $t3, 0($s3)      # Load $t3 with the base address of an array to print(printArray function works with $t3 adress)
            		jal printArray      # Function call of printArray

            		jal bomberMan       # Function call of bomberMan

            		li $v0, 4           # Syscall 4: Print string
            		la $a0, newline     # printf("\n");
            		syscall
            		la $a0, Str4        # printf("Final Board");
			li $v0, 4           # Syscall 4: Print string
			syscall
            		li $v0, 4           # Syscall 4: Print string
            		la $a0, newline     # printf("\n");
            		syscall

            		la $t3, 0($s7)      # Load $t3 with the base address of an array to print(printArray function works with $t3 adress)
			jal printArray      # Function call of printArray

            		li $v0, 10         # return 0;
            		syscall            # Syscall code for exit

####################################################
#Prints the array in t3 register
printArray:

			li $v0, 4          
			la $a0, newline             # printf("\n");  
			syscall

            		li $t0, 0                   # int i = 0;
printRow:
            		bge $t0, $s0, endPrint      # if (i >= r), exit
            		li $t1, 0                   # int j = 0;
printColumn:
            		bge $t1, $s1, nextRow      # if (j >= c), go to the next row

            		# Calculate the offset to access the current element in the 2D array

            		mul $t2, $t0, $s1           # $t2 = i * c
            		add $t2, $t2, $t1           # $t2 = i * c + j
            		add $t2, $t3, $t2           # $t2 = &array[i][j]

            		lb $a0, ($t2)               # Load character from memory
            		li $v0, 11                  # Syscall 11: Print character
            		syscall

            		addi $t1, $t1, 1            # i++;
            		j printColumn
nextRow:    
            		li $v0, 4                   
            		la $a0, newline             # printf("\n);
            		syscall
            		addi $t0, $t0, 1            # j++;
            		j printRow
endPrint:
            		li $v0, 4          
			la $a0, newline             # printf("\n);
			syscall
            		jr $ra                      # Exit function 
####################################################
#Array initalization function(subroutine)
createArray:
            		li $t1, 0                   # int i = 0;
            
            		# Calculate the total size of the 2D array
            		mul $s2, $s0, $s1           # size = r * c
            
            		# Allocate memory on the heap
            		li $v0, 9                   # Syscall 9: sbrk (allocate memory)
            		move $a0, $s2               # Size in bytes to allocate
            		syscall
            		move $t3, $v0               # $s3 holds the base address of the allocated memory
            		move $t2, $v0               # $t2 holds temp adress of base for reset
            
            		# Initialize the 2D array
initArray:
           		bge $t1, $s2, doneArray     # if(i >= size), exit
            
            		li $v0,12                   # Syscall 12: read char
            		syscall                     # scanf("%c",c);
            		beq $v0, 10, initArray      # if (c == '\n') return initArray 
            		sb $v0, ($t3)               # array[i] = c;
            
            		addi $t1, $t1, 1            # i++;
            		addi $t3, $t3, 1            # &array++;
            		j initArray
doneArray:
            		li $t1, 0                   # i = 0;
            		jr $ra                      # Exit function
####################################################
bomberMan:
            		la $s6, ($ra)               # Store return address in $s6 
            		#First Explosion
            		la $t6, 0($s3)              # Store init board to $t6 for using in createBoard function
            		jal createBoard             # Function call of createBoard function
            		la $s4, 0($t3)              # Store first board to $s4

            		#Second Explosion
            		la $t6, 0($s4)              # Store first board to $t6 for using in createBoard function
            		jal createBoard             # Function call of createBoard function
            		la $s5, 0($t3)              # Store second board to $s5

           		 #Third and final Explosion
           		 la $t6, 0($s5)              # Store second board to $t6 for using in createBoard function
            		jal createBoard             # Function call of createBoard function
            		la $s7, 0($t3)              # Store final board to $s7

            		jr $s6

####################################################
createBoard:
            		li $t1, 0                   # int i = 0;
                        
            		# Allocate memory on the heap
            		li $v0, 9                   # Syscall 9: sbrk (allocate memory)
            		move $a0, $s2               # Size in bytes to allocate
            		syscall
			move $t3, $v0               # $t3 holds the base address of the allocated memory
			move $t2, $v0               # $t2 holds temp adress of base for reset
            
# Initialize the 2D array
initArrayBoard:
			bge $t1, $s2, doneArrayBoard   # if (if i >= size) go to exit
            
			li $t0, 48 
			sb $t0, ($t3)               # next[i][j] = '0';
            
           		addi $t1, $t1, 1            # i++;
            		addi $t3, $t3, 1            # &next++;

            		j initArrayBoard
doneArrayBoard:
            		la $t3, 0($t2)              # Back to begining of an "next" array
            		li $t0, 0                   # int i = 0;
            		li $t1, 0                   # int j = 0;
            		j Loop
Loop:
            		# t6 = "previous" array
            		# t3 = "next" array
            		# t4 = current element

            		# Calculate the linear address
            		mul $t2, $t0, $s1          # $t2 = i * c
            		add $t2, $t2, $t1          # $t2 = i * c + j

            		bge $t2, $s2, endCreateBoard      # if( $t2 >= size) go to endCreateBoard


            		add $t2, $t2, $t6          # $t2 = &previous + $t2
            
           		 # Now $t2 holds the address of the desired element in the 2D array

            		# Load the value at the calculated address
           		lb $t4, 0($t2)             # $t4 = value at the calculated address
            		bne $t4, 48, notCond4      # if (current != '0') , notCond4
            
            		# Update current element to '.'
            		li $t5, 46                  
            		sub $t2, $t2, $t6          # $t2 = $t2 - &previous
            		add $t2, $t2, $t3          # $t2 = $t2 + &next
			sb $t5, ($t2)              # next[i][j] = '.';
	
            		#If statements
            
            		sub $t4,$t0,1              # i-1  t4
            		add $t7,$t0,1              # i+1  t7

            		sub $t8,$t1,1              # j-1  t8
            		add $t9,$t1,1              # j+1  t9  

            		sub $k0,$s1,1              # c-1  k0
            		sub $k1,$s0,1              # r-1  k1

            		# Update adjacent elements

            		bge $t4, $zero, cond1      # if i-1 >= 0 go to cond1
            		j notCond1                 # if not go to check other condition

cond1:
            		li $t2, 0
            		mul $t2, $t4, $s1
            		add $t2, $t2, $t1
            		add $t2, $t2, $t3
            		sb $t5, 0($t2)             # next[i - 1][j] = '.';
notCond1:
            		ble $t7, $k1, cond2        # if i+1 <= r-1 go to cond2
            		j notCond2                 # if not go to check other condition
cond2:
            		li $t2, 0
            		mul $t2, $t7, $s1
            		add $t2, $t2, $t1
            		add $t2, $t2, $t3
            		sb $t5, 0($t2)             # next[i + 1][j] = '.';
notCond2:

            		bge $t8, $zero, cond3      # if j-1 >= 0 go to cond2
            		j notCond3                 # if not go to check other condition
cond3:
            		li $t2, 0
            		mul $t2, $t0, $s1
           		add $t2, $t2, $t8
            		add $t2, $t2, $t3
            		sb $t5, 0($t2)             # next[i][j - 1] = '.';
notCond3:

            		ble $t9, $k0, cond4        # if j+1 <= c-1 go to cond3
            		j notCond4                 # if not go to check other condition
cond4:
            		li $t2, 0
            		mul $t2, $t0, $s1
            		add $t2, $t2, $t9
            		add $t2, $t2, $t3
            		sb $t5, 0($t2)             # next[i][j + 1] = '.';
notCond4:

           		 # Increment column index
            		addi $t1, $t1, 1           # i++;

            		# Check if column index reached the maximum
            		bne $t1, $s1, Loop         # if (j != c), continue the loop

            		# Reset column index and increment row index
            		li $t1, 0                  # j = 0;
            		addi $t0, $t0, 1           # i++;

           		j Loop

endCreateBoard:
            		jr $ra                      # Exit function
