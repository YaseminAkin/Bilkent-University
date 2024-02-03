		.data
regNum_p:	.asciiz "Enter register number: "
outOfBounds_p:	.asciiz "There is no such register number."
regCount_p:	.asciiz "Register count = "

		.text
Main:

		la	$a0, regNum_p		
		li	$v0, 4
		syscall				#"Enter register number: "
    		li 	$v0, 5         
    		syscall           		#input register number in $v0
    		move 	$a0, $v0    		#input register number moved to $a0 to be passed as an argument to the RegisterCount function
    		blt 	$a0, 1, outOfBound	#checking if the input is in the wanted range [1, 31]
    		bgt	$a0, 31, outOfBound	#"There is no such register number."
    		la	$a1, RegisterCount	#$a1 contains the base address (starting address) of the function RegisterCount
    		li	$a2, 84			#$a2 contains the size of the subprogram
    		add	$a2, $a2, $a1		#$a2 contains the end address of the subprogram code
    		jal 	RegisterCount   
    		move 	$t0, $v0  		#the answer returned in return register $v0, we move the value to $t0 to print it
    		li 	$v0, 4         
    		la 	$a0, regCount_p		
    		syscall                		#"Register count = "
    		li 	$v0, 1         
    		move 	$a0, $t0     
    		syscall            		#printing the answer
    		li 	$v0, 10        
    		syscall      			#terminating the program
    		     
RegisterCount:
    		
    		li	$s0, 0			#initialize register number counter
    		li	$s2, 0
    		
for1:						#loop through each instruction in the subprogram

    		bgt 	$a1, $a2, endAddress	#check if we have reached the end address ($a2)
    		lw 	$s1, 0($a1)		#read instruction from memory
    		#check rs, rd, and rt fields for the target register
    		
rs:

    		andi 	$s2, $s1, 0x03E00000  	#extract rs field
    		srl 	$s2, $s2, 21 	 	#shift rs field to the right
    		beq 	$s2, $a0, increment1  	#if rs field matches target register, increment counter

rt:

    		andi 	$s2, $s1, 0x001F0000  	#extract rt field
    		srl 	$s2, $s2, 16  		#shift rt field to the right
    		beq 	$s2, $a0, increment2  	#if rt field matches target register, increment counter

rd:

    		andi 	$s2, $s1, 0x0000F800  	#extract rd field
    		srl 	$s2, $s2, 11  		#shift rd field to the right
    		beq 	$s2, $a0, increment3  	#if rd field matches target register, increment counter

otherInstruction:

    		addi 	$a1, $a1, 4		#next instruction
    		j	for1
    
increment1:

    		addi 	$s0, $s0, 1  		#increment counter $s0
    		j 	rt	  		#continue to for1
    		
increment2:

    		addi 	$s0, $s0, 1  		#increment counter $s0
    		j 	rd	  		#continue to for1
    		
increment3:

		addi 	$s0, $s0, 1  		#increment counter $s0
    		j 	otherInstruction	#continue to for1
   	
endAddress:

		move	$v0, $s0
		jr 	$ra	
     		     		     
outOfBound:	
	
		la	$a0, outOfBounds_p
		li	$v0, 4
		syscall				#"There is no such register number."
    		li 	$v0, 10       
    		syscall           
