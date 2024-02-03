#preliminary work part for Lab1
#CS224
#Recitation No. 1
#Section No. 6
#Yasemin Akın
#22101782
#27 February 2023
	
	.data 				#variables created here is initially in ram
array: 	.space 80 			# Allocate 80 bytes = space enough to hold 20 words
numElements:
	.asciiz "enter the number of elements "
getElementsPrompt:
	.asciiz "enter the elements one by one\n"
enterAnElement:
	.asciiz "enter an element: "
getN:	.asciiz "input an integer number (N) "
menu:	.asciiz "\n\n1. Find the number of array members equal to N.\n2. Find the number of array members less than N.\nFind the number of array members greater than N.\n3. Find the number of elements evenly divisible by N.\nmake a choice "
numElEqN:
	.asciiz "Number of array elements equal to N is "
numElLess:
	.asciiz "Number of array elements less than N is "
numElGreater:
	.asciiz "\nNumber of array elements greater than N is "
numElDiv:
	.asciiz "Number of array elements divisible by N is "
	
	.text 
main: 
#initializing array values

#prompt the user to enter the number of elements
	li	$v0, 4 			#printing a string
	la 	$a0, numElements 	# point $a0 to prompt string
	syscall 			# print the prompt
#get the number of elements 
	li 	$v0, 5 			#getting integer input
	syscall 			#get int from user --> returned in $v0
	move 	$t1, $v0 		#move the resulting int to $t1 for saving it
	mul	$t3, $t1, 4		#4*numElements is $t3
#prompt the user to enter the elements one by one
	li	$v0, 4 			#printing a string
	la 	$a0, getElementsPrompt 	# point $a0 to prompt string
	syscall 			# print the prompt
#storing input values into array
	li 	$t0, 0 			#counter gets value of 0
for1:
#prompt the user to enter an element
	li 	$v0, 4
	la 	$a0, enterAnElement
	syscall
#get integer input
	li 	$v0, 5
	syscall
	move 	$t2, $v0
#store in array
	sw 	$t2, array($t0)
#increment loop counter
	addi 	$t0, $t0, 4
#check counter and loop or continue
	blt 	$t0, $t3, for1
	li 	$t0, 0 			#counter gets value of 0 again after exiting the loop

#getting value of N from user

#prompt the user to enter N
	li	$v0, 4 			#printing a string
	la 	$a0, getN 		# point $a0 to prompt string
	syscall 			# print the prompt
#get N as input
	li 	$v0, 5 			#getting integer input
	syscall 			#get int from user --> returned in $v0
	move 	$t4, $v0 		#move the resulting int to $t4 for saving it
	
#prompt the menu
	li	$v0, 4 			
	la 	$a0, menu 		
	syscall 
#get choice as input
	li 	$v0, 5 			#getting integer input
	syscall 			#get int from user --> returned in $v0
	move 	$t5, $v0 		#move the resulting int to $t4 for saving it
DoWhile:
	beq  	$t5, 1, a
	beq 	$t5, 2, b	
	beq 	$t5, 3, c
a:
	li 	$t6, 0			#loading $t6 with 0 because currently number of elements equal to N($t6) is zero
	for2:				#loopig through the array
		lw	$t1, array($t0)
		bne 	$t1, $t4, notequals
		addi	$t6, $t6, 1
		notequals:
			addi	$t0, $t0, 4
			blt 	$t0, $t3, for2	
#prompt $t6
	li	$v0, 4 			
	la 	$a0, numElEqN		
	syscall 
	li	$v0, 1 			
	move 	$a0, $t6		
	syscall	
	li 	$t0, 0 			#counter gets value of 0 again after exiting the loop
#prompt the menu again
	li	$v0, 4 			
	la 	$a0, menu 		
	syscall 
#get choice as input again
	li 	$v0, 5			#getting integer input
	syscall 			#get int from user --> returned in $v0
	move 	$t5, $v0 		#move the resulting int to $t4 for saving it
	
	beq 	$t5, 1, DoWhile
	beq 	$t5, 2, DoWhile	
	beq 	$t5, 3, DoWhile	
b:
	li 	$t6, 0			#loading $t6 with 0 because currently number of elements less than N($t6) is zero
	li 	$t7, 0			#loading $t7 with 0 because currently number of elements greater than N($t6) is zero
	for3:				#loopig through the array
		lw	$t1, array($t0)
		ble  	$t1, $t4, lessorEqual
		addi	$t7, $t7, 1
		lessorEqual:
			addi	$t0, $t0, 4
			blt 	$t0, $t3, for3
	li 	$t0, 0 			#counter gets value of 0 again after exiting the loop
	for5:				#loopig through the array
		lw	$t1, array($t0)
		bge  	$t1, $t4, greaterorEqual
		addi	$t6, $t6, 1
		greaterorEqual:
			addi	$t0, $t0, 4
			blt 	$t0, $t3, for5
#prompt $t6 (less)
	li	$v0, 4 			
	la 	$a0, numElLess		
	syscall 
	li	$v0, 1 			
	move 	$a0, $t6		
	syscall	
#prompt $t7 (greater)
	li	$v0, 4 			
	la 	$a0, numElGreater		
	syscall 
	li	$v0, 1 			
	move 	$a0, $t7		
	syscall	
	li 	$t0, 0 			#counter gets value of 0 again after exiting the loop
#prompt the menu again
	li	$v0, 4 			
	la 	$a0, menu 		
	syscall 
#get choice as input again
	li 	$v0, 5			#getting integer input
	syscall 			#get int from user --> returned in $v0
	move 	$t5, $v0 		#move the resulting int to $t4 for saving it
	
	beq 	$t5, 1, DoWhile
	beq 	$t5, 2, DoWhile	
	beq 	$t5, 3, DoWhile	

c:
	li 	$t6, 0			#loading $t6 with 0 because currently number of elements divisible by N($t6) is zero
	for4:	
		lw	$t1, array($t0)
		rem	$t7, $t1, $t4	
		bne 	$t7, 0, notdivisible
		addi	$t6, $t6, 1
		notdivisible:
			addi	$t0, $t0, 4
			blt 	$t0, $t3, for4	
	li 	$t0, 0 			#counter gets value of 0 again after exiting the loop
#prompt $t6
	li	$v0, 4 			
	la 	$a0, numElDiv		
	syscall 
	li	$v0, 1 			
	move  	$a0, $t6		
	syscall	
#prompt the menu again
	li	$v0, 4 			
	la 	$a0, menu 		
	syscall 
#get choice as input again
	li 	$v0, 5	 		#getting integer input
	syscall 			#get int from user --> returned in $v0
	move 	$t5, $v0 		#move the resulting int to $t4 for saving it
	
	beq 	$t5, 1, DoWhile
	beq 	$t5, 2, DoWhile	
	beq 	$t5, 3, DoWhile	
	

	



	



	
	
	



