#CS224
#Section 6
#Yasemin Akın
#22101782
#17 March 2023
		.data 
arr1:		.asciiz	"Entries for Array 1 has started\n"
arr2:		.asciiz	"Entries for Array 2 has started\n"
initArr_p:	.asciiz "Enter an array element: "
arr1End_p:	.asciiz	"Array 1 entries ended\n"
arr2End_p:	.asciiz	"Array 2 entries ended\n"
arr1_f:		.asciiz	"Array 1= ["
arr2_f:		.asciiz	"Array 2= ["
paranthesis:	.asciiz	"]"
space:		.asciiz ", "	
line:		.asciiz "\n"
hamming_p:	.asciiz	"\nHamming Distance is "
arraySize_p:	.asciiz	"Enter array size for both arrays: "
dot:		.asciiz	"."
cannot:		.asciiz	"Array size can not be 0. Try again!\n"

		.text 
Main:	
	li	$v0, 4			#"Enter array size for both arrays: "
	la	$a0, arraySize_p
	syscall
	li	$v0, 5			#array size in $v0
	syscall
	move	$a3, $v0		#array size in $a3 for passing it as a parameter to the subprogram
	beq 	$a3, 0, zero	
	
	li	$v0, 4			#"Entries for Array 1 has started"
	la	$a0, arr1
	syscall
	jal 	CreateArray		#Create Array 1
	move	$t1, $v0		#array 1 base address is in $t1
	li	$v0, 4			
	la	$a0, arr1End_p		#"Array 1 entries ended\n"
	syscall
	
	li	$v0, 4			#2
	la	$a0, arr2
	syscall
	jal 	CreateArray		
	move	$t2, $v0		#array 2 base address is in $t2
	li	$v0, 4			
	la	$a0, arr2End_p
	syscall	
	
	move	$a1, $t1	
	li	$v0, 4			#"Array 1= ["
	la	$a0, arr1_f		
	syscall
	jal 	PrintArray		
	li	$v0, 4			
	la	$a0, line
	syscall
	
	move	$a1, $t2
	li	$v0, 4			
	la	$a0, arr2_f		#"Array 2= [ "
	syscall
	jal 	PrintArray
	li	$v0, 4			
	la	$a0, line
	syscall
	
	move	$a2, $t1
	jal	CalculateDistance
	
#terminating the program
	li	$v0, 10
	syscall
zero:
	li	$v0, 4			
	la	$a0, cannot
	syscall
	j	Main
	
CreateArray:
	addi	$sp, $sp, -8
	mul 	$s0, $a3, 4
	move 	$a0, $s0		#size of an array * 4 (in bytes calculated for integer values)
	li	$v0, 9			#allocating, base address of the dynamic array is in $v0
	syscall
	sw	$v0, 4($sp)		#saving the base address of the array to stack because for1 loop is going to increment it and it will be lost
	move	$a1, $v0
	sw	$ra, 0($sp)		#before jumping to another function saving $ra to stack to remember where to return when the function we are currently in finishes running
	jal 	InitializeArray
	lw	$ra, 0($sp)
	lw	$v0, 4($sp)		#loading the base address value to $v0 to return it
	addi	$sp, $sp, 8
	jr 	$ra
	
InitializeArray:
	move	$s0, $a1		#moving the base address to $s0 because $v0 will be used for other purposes
	li	$s1, 0			#loading counter for number of added array elements
	for1:
		li	$v0, 4
		la	$a0, initArr_p	#prompting the user to enter an array element: "Enter an array element: "
		syscall
		li	$v0, 5		#array value in $v0
		syscall
	#store in array
		sw 	$v0, 0($s0)
	#make $s0 point to the next element's address
		addi 	$s0, $s0, 4
		addi	$s1, $s1, 1
	#check counter and loop or continue
		blt 	$s1, $a3, for1
	jr	$ra			#returning from the function
	
PrintArray:	
	move	$s0, $a1
	beq	$a3, 1, one
	li	$s1, 0			#loading counter for keeping track of number of printed array elements
	for2:
		li	$v0, 1
		lw	$a0, 0($s0)
		syscall
		li	$v0, 4	
		la	$a0, space
		syscall
	#make $a1 point to the next element's address
		addi 	$s0, $s0, 4
		addi	$s1, $s1, 1
	#check counter and loop or continue
		addi	$s2, $a3, -1
		blt 	$s1, $s2, for2
	one:
		li	$v0, 1
		lw	$a0, 0($s0)
		syscall
		li	$v0, 4	
		la	$a0, paranthesis
		syscall
	jr	$ra		

CalculateDistance:
	li	$s1, 0
	li	$s2, 0
	for3:	
		lw	$s3, 0($a2)
		lw	$s5, 0($a1)
		beq	$s3, $s5, noIncrement
		addi 	$s2, $s2, 1
		noIncrement:
			addi 	$a2, $a2, 4
			addi 	$a1, $a1, 4
			addi 	$s1, $s1, 1
		blt	$s1, $a3, for3
	li	$v0, 4			
	la	$a0, hamming_p
	syscall
	li	$v0, 1
	move	$a0, $s2
	syscall
	li	$v0, 4			
	la	$a0, dot
	syscall
	jr 	$ra
	
	
	
	
	
	
	
	
	
	
	
	
