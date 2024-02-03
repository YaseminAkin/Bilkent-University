	.text
# text segment contains instructions
	lw	$t0, a
   	lw	$t1, b
   	add	$t2, $t0, $t1
   	sw	$t2, sum
   
# Print msg
	li	$v0, 4
	la	$a0, msg
	syscall
	
# Print sum
	li	$v0, 1
	lw	$a0, sum
	syscall
	
# Stop execution
	li	$v0, 10
	syscall
   	 	
   	.data
 # data segment contains variable definitions
 a:	.word	10
 b:	.word	20
 sum:	.space	4
 msg:	.asciiz	"sum: "