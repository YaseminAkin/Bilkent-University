		.data
size_p:		.asciiz "Enter the size for linked list: "
value_p:	.asciiz "Enter integer value: "
start_s:	.asciiz "<"
end_s:		.asciiz ">\n"
space:		.asciiz ", "
list_p:		.asciiz "List: "
sizeZero_p:	.asciiz "Size can not be zero or negative, enter another positive integer value: "
reverseList_p:	.asciiz "List printed in reverse order: "

		
		.text
Main: 

		jal	createLinkedList
#Linked list is pointed by $v0
		move	$t0, $v0	#linked list address in $t0
		move	$t1, $v1	#size of the linked list is in $t1
		la	$a0, list_p
		li	$v0, 4
		syscall			#"List before removal: "
		move	$a0, $t0	#Pass the linked list address in $a0
		move	$a1, $t1	#size of the linked list is passed in $a1
		jal	printLinkedList
		move	$a1, $v0	#Pass the linked list address in $a1
		move	$a2, $v1
		la	$a0, reverseList_p
		li	$v0, 4
		syscall
		jal	PrintInReverseOrder
		li	$v0, 10
		syscall			#terminating the program
		
PrintInReverseOrder:
#$a1 base address of the linked list
#$a2 size of the linked list
		addi 	$sp, $sp, -8 
		sw 	$a1, 0($sp)
		sw 	$ra, 4($sp) 
		li	$s0, 0
		bne 	$a1, 0, recurse 
#base-case
		addi 	$sp, $sp, 8 
		jr 	$ra 
		
recurse:

		lw 	$a1, 0($a1) 
		jal 	PrintInReverseOrder
		lw 	$a1, 0($sp)
		lw 	$ra, 4($sp) 
		addi 	$sp, $sp, 8 
		lw 	$a0, 4($a1) 
		li 	$v0, 1 
		syscall
		addi	$s0, $s0, 1
		beq	$a2, $s0, noSpace
		la 	$a0, space
		li 	$v0, 4
		syscall
noSpace:
		jr 	$ra             
		
createLinkedList:
	
		la	$a0, size_p
		li	$v0, 4
		syscall			#"Enter the size for linked list: "
size:
		li	$v0, 5
		syscall
		ble	$v0, 0, sizeZero
		move 	$s0, $v0	#number of nodes to be created is in $s0 now	
		li	$s1, 1		#$s1: Node counter
#Create the first node: header.
#Each node is 8 bytes: link field then data field.
		li	$a0, 8		
		li	$v0, 9
		syscall			#(dynamically creating the node)
#OK now we have the list head. Save list head pointer 
		move	$s2, $v0	#$s2 points to the first and last node of the linked list.
		move	$s3, $v0	#$s3 now points to the list head.
		la	$a0, value_p
		li	$v0, 4
		syscall			#"Enter integer value: "
		li	$v0, 5
		syscall
		move	$s4, $v0
		sw	$s4, 4($s2)	#Store the data value.
	
add:

		beq	$s1, $s0, allDone	#No. of nodes created compared with the number of nodes to be created.
		addi	$s1, $s1, 1	#Increment node counter.
		li	$a0, 8 		#Remember: Node size is 8 bytes.
		li	$v0, 9
		syscall

		sw	$v0, 0($s2)	#Connect the this node to the lst node pointed by $s2.
#Now make $s2 pointing to the newly created node.
		move	$s2, $v0	# $s2 now points to the new node.
		la	$a0, value_p
		li	$v0, 4
		syscall			#"Enter integer value: "
		li	$v0, 5
		syscall
		move	$s4, $v0
		sw	$s4, 4($s2)	#Store the data value.
		j	add
allDone:
#Make sure that the link field of the last node cotains 0.
#The last node is pointed by $s2.
		sw	$zero, 0($s2)
		move	$v0, $s3	#Now $v0 points to the list head ($s3).
		move	$v1, $s0
		jr	$ra
#=========================================================
printLinkedList:

		addi	$sp, $sp, -8
		sw	$a0, 0($sp)
		sw	$a1, 4($sp)
#$a0: points to the linked list.
		move 	$s0, $a0	#$s0: points to the current node.
		li	$s3, 0		#node counter: $s3
		la	$a0, start_s
		li	$v0, 4
		syscall			#Print "<"
		
		
printNextNode:
					#$s0: Address of current node
		lw	$s1, 0($s0)	#$s1: Address of next node
		lw	$s2, 4($s0)	#$s2: Data of current node
		addi	$s3, $s3, 1
		move	$a0, $s2	#$s2: Data of current node
		li	$v0, 1		
		syscall	
		bge	$s3, $a1, printedAll
		la	$a0, space
		li	$v0, 4
		syscall			#Print ", "
		
#Now consider next node.
		move	$s0, $s1	#Consider next node.
		j	printNextNode
		
printedAll:
#Restore the register values
		la	$a0, end_s
		li	$v0, 4
		syscall			#Print ">"
		lw	$v0, 0($sp)
		lw	$v1, 4($sp)
		addi	$sp, $sp, 8
		jr	$ra
		
sizeZero:
		
		la	$a0, sizeZero_p
		li	$v0, 4
		syscall
		j	size