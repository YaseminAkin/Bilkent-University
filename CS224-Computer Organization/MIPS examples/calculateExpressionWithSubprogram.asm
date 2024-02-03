	.text
# Calculate x= max(a, b) + max(c, d)
	lw	$a0, a
	lw	$a1, b
	lw	$a2, c
	lw	$a3, d
	jal	calculate # Returns result in $v0
	
	move	$a0, $v0
	li	$v0, 1
	syscall
	
	li	$v0, 10
	syscall
	
#=======================================================
calculate:
# Assume that we are not allowed to use $t registers/
# Use $s registers before using them
# Save $ra since this subprogram invokes max: $ra will be lost
	addi	$sp, $sp, -16	# allocate room for 4 items
	sw	$s0, 12($sp)
	sw	$s1, 8($sp)
	sw	$s2, 4($sp)
	sw	$ra, 0($sp)
	jal 	max	
	move	$s0, $v0
# $s0= $v0= max(a, b)
	
# Now invoke max(c, d)
	move	$a0, $a2
	move	$a1, $a3
	jal	max
	move	$s1, $v0
# $s1= $v0= max(c, d)
	add	$s2, $s0, $s1
# Return result in $v0
	move	$v0, $s2
	
# Restore the values of $ra, $s0, $s1, $s2
	lw	$ra, 0($sp)
	lw	$s2, 4($sp)
	lw	$s1, 8($sp)
	lw	$s0, 12($sp)	
	jr	$ra	
#======================================================
max:
# Find the maximum of numbers stored in $a0 and $a1 return it in $vo
	move	$v0, $a0
	bge	$v0, $a1, done
	move	$v0, $a1
done:	jr	$ra

	.data
a:	.word	5
b:	.word	10
c:	.word	15
d:	.word	20
x:	.space	4