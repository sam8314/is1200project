  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,17	# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

hexasc:	li	$t1, 10
	slt 	$t0, $a0, $t1	
	beq 	$t0, $0, letter
	nop
	addi 	$v0, $a0, 0x30	# code in ascii	
	
	jr	$ra		# return to caller
	nop
	
letter:	addi 	$v0, $a0, 0x37	# code in ascii
	jr 	$ra		# return to caller function
	nop
