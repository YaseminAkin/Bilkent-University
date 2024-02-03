##
## Program1.asm - prints out "hello world"
##
##	a0 - points to the string
##

#################################
#					 	#
#		text segment		#
#						#
#CS224
#Recitation No. 1
#Section No. 6
#Yasemin Akın
#22101782
#27 February 2023
#################################

	.text		
	.globl __start 

__start:		# execution starts here
	la $a0,str	# put string address into a0
	li $v0,4	# system call to print
	syscall		#   out a string

	li $v0,10  # system call to exit
	syscall	#    bye bye


#################################
#					 	#
#     	 data segment		#
#						#
#################################

	.data
str:	.asciiz "Hello <Sanaz Gheibun>"
n:	.word	10

##
## end of file Program1.asm

