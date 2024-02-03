	.text
# Find sum of array elements and print

	la	$t0, array		# $t0: array pointer
	lw	$t1, arraysize		#$t1: No of array elements remaining to add
	add	$t2, $zero, $zero	# $t2: sum
next:	
	beq	$t1, $zero, done	# Are we done: proccessed all elements?
	lw	$t3, 0($t0)		# Get the next element to be added
	add	$t2, $t2, $t3		# sum= sum + $t3
	addi	$t1, $t1, -1
	addi	$t0, $t0, 4		# Update array pointer $t0
	j	next			# Go to next
done:
	sw	$t2, result
	
	la	$a0, mesaj1
	li	$v0, 4			# Display mesaj1
	syscall
	
	lw	$a0, result
	li	$v0, 1
	syscall				# Print result
	
#	stop
	li	$v0, 10
	syscall
	
	
	.data
array:	.word	5, 10, 20
arraysize:
	.word	3	# No. of data items in array.
result:	.space	4	# Allocate 4 bytes to store result
mesaj1:	.asciiz	"sum:"
	
	
