#CS224
#Recitation No. 1
#Section No. 6
#Yasemin Akın
#22101782
#3 March 2023
			.data 

enterOperandA: 	.asciiz "enter operand a: "
enterOperandB: 	.asciiz "enter operand b: "
enterOperandC: 	.asciiz "enter operand c: "
result:		.asciiz "result is: "
divisorZero:	.asciiz "divisor can not be 0!"

		.text
main:
#promt user to enter a
		li	$v0, 4		#printing a string
		la 	$a0, enterOperandA
		syscall
#get int input to be used as a
		li	$v0, 5		#reading integer
		syscall
		move	$t1, $v0	#saving integer input a to $t1 = a
#promt user to enter b
		li	$v0, 4		#printing a string
		la 	$a0, enterOperandB
		syscall
#get int input to be used as b
		li	$v0, 5		#reading integer
		syscall
		move	$t2, $v0	#saving integer input a to $t2 = b
#promt user to enter c
		li	$v0, 4		#printing a string
		la 	$a0, enterOperandC
		syscall
#get int input to be used as c
		li	$v0, 5		#reading integer
		syscall
		move	$t3, $v0	#saving integer input a to $t3 = c
		
		
		
		jal evaluate
		beq 	$t1, 0, zero
		
#promt user the answer
		li	$v0, 4		#printing a string
		la 	$a0, result
		syscall
		
		li	$v0, 3
		mov.d  	$f12, $f0
		syscall
#exit the program
		li	$v0, 10
		syscall
		
zero:
#promt user the divZero promt
		li	$v0, 4		#printing a string
		la 	$a0, divisorZero
		syscall
		
#exit the program
		li	$v0, 10
		syscall


evaluate:
		mult  	$t1, $t2
		mflo 	$t4		#a x b in $t4
		add 	$t2, $t1, $t2	#a + b in $t2
		sub	$t2, $t4, $t2	#dividend in $t2
		rem   	$t1, $t1, $t3	#a mod c in $t1 (divisor)
		beq 	$t1, 0, done
		
		
		mtc1  	$t1, $f2
		cvt.d.w $f2, $f2
		mtc1 	$t2, $f4
		cvt.d.w $f4, $f4
		
		div.d 	$f0, $f4, $f2	
done:		
		
		jr 	$ra
	
		
		
		

	


	
	