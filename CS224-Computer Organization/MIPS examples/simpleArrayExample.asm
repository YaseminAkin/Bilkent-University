	.text
	la	$t0, array
	lw	$t1, 0($t0)
	
	lw	$t2, 4($t0)
	
	addi	$t0, $t0, 8
	lw	$t3, 0($t0)
	
	move	$t1, $t3	# move is a PSEUDO instruction
	
	li	$v0, 10
	syscall
	
	.data
array:	.word	10, 20, 30
array2:	.space 	400