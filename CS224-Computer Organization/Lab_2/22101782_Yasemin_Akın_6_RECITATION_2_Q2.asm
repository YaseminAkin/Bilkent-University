#CS224
#Section 6
#Yasemin Akın
#22101782
#17 March 2023
		.data
arraySize_p:	.asciiz	"Enter array size: "
dot:		.asciiz	"."
cannot:		.asciiz	"Array size can not be 0. Try again!\n"
paranthesis:	.asciiz	"]"
space:		.asciiz ", "	
line:		.asciiz "\n"
arr_f:		.asciiz	"Array= ["
arr:		.asciiz	"Entries for array has started\n"
initArr_p:	.asciiz "Enter an array element: "
arrEnd_p:	.asciiz	"Array entries ended\n"
index_p:	.asciiz	"Enter an index position: "
count_p:	.asciiz "Index possition appearance count: "
indexBound:	.asciiz	"Index out of bounds. Try again!\n"
	
		.text
Main:
	jal 	CreateArray		#Create Array 
	move	$a1, $v0		#array 1 base address is in $a1	
	jal 	PrintArray
	jal 	indexCount
	
#terminating the program
	li	$v0, 10
	syscall
	
zero:
	li	$v0, 4			
	la	$a0, cannot
	syscall
	j	CreateArray

CreateArray:
	addi	$sp, $sp, -8
	li	$v0, 4			#"Enter array size: "
	la	$a0, arraySize_p
	syscall
	li	$v0, 5			#array size in $v0
	syscall
	move	$a3, $v0		#array size in $a3 for passing it as a parameter to the subprogram
	beq 	$a3, 0, zero	
	
	li	$v0, 4			#"Entries for array has started"
	la	$a0, arr
	syscall
	mul 	$s0, $a3, 4
	move 	$a0, $s0		#size of an array * 4 (in bytes calculated for integer values)
	li	$v0, 9			#allocating, base address of the dynamic array is in $v0
	syscall
	sw	$v0, 4($sp)		#saving the base address of the array to stack because for1 loop is going to increment it and it will be lost
	move	$a1, $v0
	sw	$ra, 0($sp)		#before jumping to another function saving $ra to stack to remember where to return when the function we are currently in finishes running
	jal 	InitializeArray
	li	$v0, 4			
	la	$a0, arrEnd_p		#"Array entries ended\n"
	syscall
	lw	$ra, 0($sp)
	lw	$v0, 4($sp)		#loading the base address value to $v0 to return it
	addi	$sp, $sp, 8
	jr 	$ra
	
InitializeArray:
	move	$s0, $a1		
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
	li	$v0, 4			#"Array= ["
	la	$a0, arr_f		
	syscall
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
	li	$v0, 4			
	la	$a0, line
	syscall
	jr	$ra	
	
indexCount:
	li 	$s1, 0		#counter
	li	$v0, 4			
	la	$a0, index_p
	syscall
	li	$v0, 5		#index value in $v0
	syscall
	move	$s0, $v0	#index value in $s0
	addi	$s4, $a3, -1
	bgt	$s0, $s4, noIndex
	blt	$s0, 0, noIndex
	addi	$sp, $sp, -4
	sw	$a1, 0($sp)
	for:
		beq	$s1, $s0, indexFound
		addi	$s1, $s1, 1
		addi	$a1, $a1, 4
		bne	$s1, $s0, for
	indexFound:
		lw 	$s2, 0($a1)	#integer at given index is in $s2
		li 	$s1, 0		#counter for loop
		li 	$s0, 0		#counter for the count
	lw	$a1, 0($sp)
	sw	$a1, 0($sp)
	for3:	
		lw	$s3, 0($a1)
		bne	$s2, $s3, noIncrement
		addi	$s0, $s0, 1
		noIncrement:
			addi	$s1, $s1, 1
			addi	$a1, $a1, 4
			bne	$s1, $a3, for3
	li	$v0, 4			
	la	$a0, count_p
	syscall
	li	$v0, 1
	move	$a0, $s0
	syscall
	li	$v0, 4			
	la	$a0, line
	syscall
	move	$v0, $s0
	jr	$ra
	noIndex:
		li	$v0, 4			
		la	$a0, indexBound
		syscall
		j	indexCount
		
		
		
	

		
		
	
	

	
	
	
	
	
	
	
	
	