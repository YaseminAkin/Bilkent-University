.data


printElement : .asciiz "Array Element : "



.text #code section
main:#main program starts from here

addiu $sp,$sp,-16 #make space in stack 16 bytes
jal create_array #call function create_array
jal print_array #call function print_array
addiu $sp,$sp,16 #get back stack to top

#terminate program
li $v0,10 #syscall 10 to terminate program
syscall

#function create_array
create_array:
sw $ra,12($sp) #sp+12 = ra(address of function calling)

sw $v0,0($sp) # sp+0 = $v0(array length)
jal allocate_array #call function allocate_array
#sp+0 = array length
#sp+4 = array base address
#but read_array sp+0=array base address and sp+4 = array length
lw $a0,0($sp) #$a0(array length) = sp+0
lw $a1,4($sp) #$a1(array address) = sp+4

sw $a1,0($sp) #sp+0 = array base address
sw $a0,4($sp) #sp+4 = array length

jal read_array #call function read_array

lw $ra,12($sp) #ra = sp+12
#ra = address from this function called +4
jr $ra #jump to address saved in $ra

#end of create_array subprogram
#function allocate_array
allocate_array:
lw $a0,0($sp) #$a0 =array length from $sp+0
#$a0 = number of bytes to allocate
#each integer takes 4 bytes
#so we need array length * 4= total bytes space
sll $a0,$a0,2 #$a0 = $a0<<2 = $a0*4

li $v0,9 #syscall 9 to dynamic allocate memory of $a0 bytes
syscall

#$v0 = address of dynamic memory
sw $v0,4($sp) # $sp+4 = array base address
#ra = address from this function called +4
jr $ra #jump to address saved in $ra

#end of allocate_array subprogram

#function read_array
read_array:
lw $a2,0($sp) #$a2 = array base address
lw $a1,4($sp) #$a1 = array length


readForLoop: #loop from array length to 0
#if array length == 0 jump to returnReadArray
beqz $a1,returnReadArray

#print promptIntStr on console
la $a0,promptIntStr #$a0 = address of promptIntStr
li $v0,4 #syscall 4 to print string
syscall
#read integer saved in $v0
li $v0,5 #syscall to read integer
syscall

sw $v0,0($a2) #Array[index]=$v0(user input)
addiu $a2,$a2,4 #point to next element address

addi $a1,$a1,-1 #decrement array length by 1
j readForLoop #jump to readForLoop label



returnReadArray:
#ra = address from this function called +4
jr $ra #jump to address saved in $ra

#end of read_array subprogram

#function print_array
print_array:
lw $a2,0($sp) #$a2 = array base address
lw $a1,4($sp) #$a1 = array length

#print printElement on console
la $a0,printElement #$a0 = address of printElement
li $v0,4 #syscall 4 to print string
syscall



printForLoop: #loop from array length to 0
#if array length == 0 jump to returnPrintArray
beqz $a1,returnPrintArray

lw $a0,0($a2) #$a0 = *Array= *$a2
li $v0,1 #syscall 1 to print integer saved in $a0
syscall

#print space on console
la $a0,space #$a0 = address of space string
li $v0,4 #syscall 4 to print string
syscall


addiu $a2,$a2,4 #point to next element address
addi $a1,$a1,-1 #decrement array length by 1
j printForLoop #jump to printForLoop label



returnPrintArray:
#ra = address from this function called +4
jr $ra #jump to address saved in $ra

#end of read_array subprogram

