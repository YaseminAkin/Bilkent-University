		.data
size_p:		.asciiz "Enter the size for linked list: "
value_p:	.asciiz "Enter integer value: "
start_s:	.asciiz "<"
end_s:		.asciiz ">"
space:		.asciiz ", "
ogList_p:	.asciiz "List before removal: "
afterList_p:	.asciiz "List after removal: "
removeEl_p:	.asciiz "\nEnter the number to be removed from the list above: "
sizeZero_p:	.asciiz "Size can not be zero or negative, enter another positive integer value: "

		.text
Main: 

		jal	createLinkedList
#Linked list is pointed by $v0
		move	$t0, $v0	#linked list address in $t0
		move	$t1, $v1	#size of the linked list is in $t1
		la	$a0, ogList_p
		li	$v0, 4
		syscall			#"List before removal: "
		move	$a0, $t0	#Pass the linked list address in $a0
		move	$a1, $t1	#size of the linked list is passed in $a1
		jal	printLinkedList
		move	$a0, $v0	#Pass the linked list address in $a0
		move	$a1, $v1	#size of the linked list is passed in $a1
		jal	CopyAllExcept_x
		move	$t0, $v0	#linked list address in $t0
		move	$t1, $v1	#size of the linked list is in $t1
		la	$a0, afterList_p
		li	$v0, 4
		syscall			#"List after removal: "
		move	$a0, $t0	#Pass the linked list address in $a0
		move	$a1, $t1	#size of the linked list is passed in $a1
		jal	printLinkedList
		li	$v0, 10
		syscall			#terminating the program

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
		
CopyAllExcept_x:

    		move	$s7, $a0
		la	$a0, removeEl_p	
		li 	$v0, 4
		syscall
		li	$v0, 5
		syscall
		move	$s0, $v0	#$s0: element to be removed
		
    		
   		li 	$s1, 0          #Initialize a counter for the size of the new linked list
   		li	$a0, 8 		#Remember: Node size is 8 bytes.
		li	$v0, 9
		syscall
		move	$s2, $v0	#Create a new node for the new linked list
		move	$s3, $v0	#$s3 is the head pointer of the new linked list
    
loop:

		beq	$s7, 0, end
		lw	$s6, 0($s7)	#$s6: points to the next node (pointing means containing the address of the pointed element!)	
    		lw 	$s4, 4($s7)	#Load the value of the current node
    		beq 	$s4, $s0, next	#Check if the value is the one to exclude, if yes move to the next node and do not copy it into the new list
    		sw 	$s4, 4($s2)     #Store the value in the new node
    		addi 	$s1, $s1, 1     #Increment the size counter
    		li	$a0, 8 		#Remember: Node size is 8 bytes.
		li	$v0, 9
		syscall
		sw	$v0, 0($s2)	#Create a new node for the new linked list
		move	$s2, $v0	#point to the new node of the new linked list (=point next at the new list)
    
#since we manipulate two lists in this function, here we move forward in the OG list, above we move forward in the new list
next:
    		move 	$s7, $s6	#Move to the next node in the original linked list (same line can be written as: move	$s7, 0($s7) without using an extra register $s6 but it is a better practise to use!
    		j 	loop

end:

    		sw 	$zero, 0($s2)	#Set the next pointer of the last node to NULL
    		move 	$v0, $s3	#Return the base address of the new linked list
    		move 	$v1, $s1	#Return the size of the new linked list
    		jr	$ra

sizeZero:
		
		la	$a0, sizeZero_p
		li	$v0, 4
		syscall
		j	size