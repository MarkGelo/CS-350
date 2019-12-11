.data 0x10000000
	msg1: .asciiz "Please enter an integer number: "
        bye: 	.asciiz "\nHave a good day!\n "

.text
.globl main
	
	main: 
		addu $s0, $ra, $0 	# save $31 in $16
		li $v0, 4 		# system call for print_str
		la $a0, msg1 		# address of string to print
		syscall
		
		jal readfromkeyboard

		# do some computation here with the number
		addu $t0, $v0, $0 	# move the number in $t0
		sll $t1, $t0, 2 	
		
		# print the result
		li $v0, 1 		# system call for print_int
		addu $a0, $t1, $0 	# move number to print in $a0
		syscall
		
		# restore now the return address in $ra and return from main
		addu $ra, $0, $s0 	# return address back in $31
		b end
        
        readfromkeyboard:
		# now get an integer from the user
		li $v0, 5 		# system call for read_int
		syscall 		# the integer placed in $v0
		jr $ra
	end: 
		li $v0, 4 	     	# system call code for Print String
		la $a0, bye	     	# load address of msg. into $a0
		syscall 	     # print the string
		li $v0, 10 	     	# terminate program run and
		syscall