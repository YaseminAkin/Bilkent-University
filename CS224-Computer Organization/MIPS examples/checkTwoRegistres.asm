	.text
	li	$a0, 2
	li	$a1, 0
	jal	rTheyEqual
	
	move	$a0, $v0
	li	$v0, 1
	syscall
	
	li	$v0, 10
	syscall
	
rTheyEqual:
	xor	$t0, $a0, $a1
	nor	$v0, $zero, $t0
	srl	$v0, $v0, 31
	jr	$ra