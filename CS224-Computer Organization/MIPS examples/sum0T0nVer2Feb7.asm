 # Find sum of numbers from 0 to n (n >= 0)
 # Use MARS Menu Find: Tools/InstructionStatistics/Mark: Connect to MIPS
 # Bottom Test: MORE efficient WHY?
 	.text
 	lw	$t0, n		   # $t0: i
 	add	$t1, $zero, $zero  # $t1: total
 	j	test
 next:
 	add	$t1, $t1, $t0
 	addi	$t0, $t0, -1
test:
	bne	$t0, $zero, next
	
 	sw	$t1, sum
 # Print sum	
 	li	$v0, 1
 	lw	$a0, sum
 	syscall
 # Stop	
 	li	$v0, 10
 	syscall
 	
 	.data
 n:	.word	3
 sum: 	.space 	4