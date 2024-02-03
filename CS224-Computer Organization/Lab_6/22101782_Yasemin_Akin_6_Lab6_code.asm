#Course No.: CS224
#Lab No.: 6
#Section No.: 6
#Full Name: Yasemin Akın
#Bilkent ID.: 22101782

		
		.data 
rPrompt: 	.asciiz "\nSummation of matrix elements in row by row major: " 
cPrompt: 	.asciiz "\nSummation of matrix elements in column by column major: " 

	
		.text 
Main:
		jal 	do
			 
		li 	$v0, 10 
		syscall
		
do:
		addi	$sp, $sp, -4
		sw	$ra, 0($sp)
		li	$s0, 50
		mul 	$s2, $s0, $s0 		# number of elements in array in $s2
		mul 	$a0, $s2, 4 
		li 	$v0, 9 
		syscall 
		move 	$s1, $v0 		# array base address in $s1
		move	$s7, $s1
		# insertion starting from 1
		li 	$t0, 1 
		
insert:
		sw 	$t0, 0($s7) 
		addi 	$s7, $s7, 4 
		addi 	$t0, $t0, 1 
		ble	$t0, $s2, insert
		
		jal	columnSum
			
		lw	$ra, 0($sp)
		addi	$sp, $sp, 4
		jr	$ra
		
# row by row summation		
rowSum: 	
		addi 	$sp, $sp, -12 
		sw 	$s1, 0($sp)
		sw 	$s2, 4($sp)
		sw	$ra, 8($sp)
	
		mul 	$s4, $s0, 4 		# column offset in $s4
		li 	$s3, 0 			# total sum in $s3
		li 	$t1, 0 			# row - 1 in $t1
		
loopC2:
		mul 	$s5, $t1, 4 		# row offset in $s5
		move 	$s6, $0 		# column - 1 in $s6  
		add 	$t5, $s1, $s5 		# address in $t5
		lw 	$t7, 0($t5) 		# current element in $t7
		add 	$s3, $t7, $s3 		
		
loopR:
		add 	$t5, $s4, $t5 		# address in $t5
		lw 	$t7, 0($t5) 		# current element in $t7
		add 	$s3, $t7, $s3 		
		addi 	$s6, $s6, 1 		# column + 1
		blt 	$s6, $s0, loopR 	# if #column < N(in $s0) then cont
		addi 	$t1, $t1, 1 		# row + 1
		blt 	$t1, $s0, loopC2
	
		li 	$v0, 4 
		la 	$a0, rPrompt
		syscall
		move 	$a0, $s3
		li 	$v0, 1
		syscall 
	
		lw	$ra, 8($sp)
		lw 	$s2, 4($sp)
		lw 	$s1, 0($sp)
		addi 	$sp, $sp, 12
		jr	$ra
		
# column by column summation
columnSum: 	
		addi 	$sp, $sp, -12 
		sw 	$s1, 0($sp)
		sw 	$s2, 4($sp)
		sw	$ra, 8($sp)
		
		li 	$s3, 0 			# total sum in $s3

loopC:
		lw 	$s4, 0($s1) 		# current item to add in $s4
		addi 	$s1, $s1, 4 
		add 	$s3, $s3, $s4 	
		subi 	$s2, $s2, 1
		bgt 	$s2, 0, loopC
		
		li 	$v0, 4 
		la 	$a0, cPrompt 
		syscall
		move 	$a0, $s3
		li 	$v0, 1
		syscall 
	
		lw	$ra, 8($sp)
		lw 	$s2, 4($sp)
		lw 	$s1, 0($sp)
		addi 	$sp, $sp, 12
 		jr 	$ra
