		.data
dividend_p:	.asciiz "Enter dividend: "
divisor_p:	.asciiz "Enter divisor: "
negative_p:	.asciiz "Entered integer can not be negative! Quitting..."
zeroDivisor_p:	.asciiz "Divisor can not be zero! Quitting..."
quotient_p:	.asciiz "quotient = "
remainder_p:	.asciiz "\nremainder = "
		
		.text 
Main:

		la	$a0, dividend_p
		li	$v0, 4
		syscall				#"Enter dividend: "
		li 	$v0, 5         
    		syscall           
    		move 	$a1, $v0 		#Dividend in $a1
    		la	$a0, divisor_p		
		li	$v0, 4
		syscall				#"Enter divisor: "
		li 	$v0, 5         
    		syscall           
    		move 	$a2, $v0 		#Divisor in $a2
    		jal	recursiveDivision
    		move	$t0, $a0		#move quotient from returned value $v0 to $t0
    		move	$t1, $a1		#move remainder from returned value $a1 to $t1
    		la	$a0, quotient_p
		li	$v0, 4
		syscall				#"quotient = "
		move	$a0, $t0
		li 	$v0, 1
		syscall				#print quotient
		la	$a0, remainder_p	
		li	$v0, 4
		syscall				#"remainder = "
		move	$a0, $t1
		li 	$v0, 1
		syscall				#print remainder
    		li 	$v0, 10		
    		syscall				#terminating the program
   
negative:
	
		la	$a0, negative_p
		li	$v0, 4
		syscall				#"Entered integer can not be negative! Quitting..."
		li 	$v0, 10
    		syscall				#terminating the program

zeroDivisor:
	
		la	$a0, zeroDivisor_p
		li	$v0, 4
		syscall				#"Divisor can not be zero! Quitting..."
		li 	$v0, 10
    		syscall				#terminating the program

recursiveDivision:
#base cases
    		addi 	$sp, $sp, -4     	#allocate space for $ra register on the stack
    		sw   	$ra, 0($sp)       	#save return address on the stack
    		li   	$s0, 0            	#initialize quotient to 0 ($s0)
    		blt	$a1, 0, negative	#check for negativity (base case for our implementation of division)
    		blt	$a2, 0, negative	#check for negativity (base case for our implementation of division)
    		beq	$a2, 0, zeroDivisor	#check for zero divisor (true base case)
#recursively subtract the divisor from the dividend
    		
recurse:
#recursive case
    		sub  	$a1, $a1, $a2    	#subtract divisor from dividend
    		bgez 	$a1, increaseQuotient   #if dividend is non-negative, continue
    		add  	$a1, $a1, $a2  		#restore dividend (which is equal to final reminder)
    		j    	return               	#dividend is negative, exit recursion
    		
increaseQuotient:

    		addi 	$s0, $s0, 1       	#increment quotient
    		j    	recurse           	#continue recursion

return:

		move 	$a0, $s0        	#move quotient to return value $a0
		move	$a1, $a1		#move reminder to intended return value $a1
    		lw   	$ra, 0($sp)      	#restore return address
    		addi 	$sp, $sp, 4     	#deallocate space for $ra register on the stack
    		jr   	$ra             	#return
