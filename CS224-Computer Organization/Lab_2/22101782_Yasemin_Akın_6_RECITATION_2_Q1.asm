#CS224
#Section 6
#Yasemin Akın
#22101782
#17 March 2023
		.data
enterInteger:	.asciiz	"Enter integer 1: "
enterInteger2:	.asciiz	"Enter integer 2: "
int1Hex:	.asciiz	"Integer 1 hexadecimal value= "
int2Hex:	.asciiz	"Integer 2 hexadecimal value= "
hamming_p:	.asciiz	"\nHamming Distance is "
continue_p:	.asciiz	"\nDo you want to continue? If yes enter 0, any other integer to exit: "
line:		.asciiz "\n"
dot:		.asciiz	"."

		.text
Main:
	jal 	enterPrintHamming
	beq	$v0, 0, enterPrintHamming
	
	li	$v0, 10
	syscall

enterPrintHamming:
	li	$s4, 0
	li	$s5, 0
	li	$v0, 4			
	la	$a0, enterInteger
	syscall
	li	$v0, 5		#int value in $v0
	syscall
	move	$s0, $v0	#int1 value in $s0
	move	$s6, $s0
	
	
	li	$v0, 4			
	la	$a0, enterInteger2
	syscall
	li	$v0, 5		#int value in $v0
	syscall
	move	$s1, $v0	#int2 value in $s1
	move	$s7, $s1
	
	for5:
		beq	$s5, 32, exit
		andi	$s2, $s0, 1
		andi	$s3, $s1, 1
		srl	$s0, $s0, 1
		srl	$s1, $s1, 1
		addi	$s5, $s5, 1
		beq	$s2, $s3, for5
		addi	$s4, $s4, 1
		j 	for5
	#printing found values
	exit:
		li	$v0, 4			
		la	$a0, int1Hex
		syscall
		li	$v0, 34	
		move	$a0, $s6
		syscall
		li	$v0, 4			
		la	$a0, line
		syscall
		li	$v0, 4			
		la	$a0, int2Hex
		syscall
		li	$v0, 34	
		move	$a0, $s7
		syscall
		li	$v0, 4			
		la	$a0, hamming_p
		syscall
		li	$v0, 1			
		move	$a0, $s4
		syscall
		li	$v0, 4			
		la	$a0, dot
		syscall
		li	$v0, 4			
		la	$a0, continue_p
		syscall
		li	$v0, 5		
		syscall
		jr	$ra
