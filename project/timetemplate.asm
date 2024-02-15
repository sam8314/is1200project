  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x00005959
timstr:	.ascii "This is a ticking time bomb in reverse.\n"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,3
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop

	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

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
		

delay:
    	PUSH	($ra)  
    	PUSH	($a0)           
    	move  	$t0, $a0
    	bne 	$t0,$zero, .delay_loop
    	nop

.delay_loop:
    	li 	$t1, 10	#number of loops

.inner_loop:
    	subi 	$t1, $t1, 1
   	bne 	$t1, $zero, .inner_loop
   	nop

    	subi 	$t0, $t0, 1
    	bne 	$t0, $zero, .delay_loop
    	nop

	POP	($a0)
    	POP	($ra)              	
    	jr 	$ra	#go back to caller
    	nop
			
time2string:	
	#saving the saved registers
	PUSH 	($ra)
	PUSH	($t0)
	PUSH	($t1)
	PUSH	($t2)
	PUSH	($t3)
	PUSH	($t4)
	PUSH	($t5)
	PUSH	($s0)
	PUSH	($s1)
	PUSH	($s2)
	PUSH	($s3)
	PUSH	($s4)
	move 	$t0, $a0	#copy base address
		
	# building the blocks
	move	$s0, $a1	#t0 = a1 0x00001653
	andi	$s0, $s0, 0xF000	#get 4th bit of a1 : 1
	srl	$s0, $s0, 12	
	PUSH	($a0)
	move	$a0, $s0	#store it in a0, the input arg for hexasc
	jal 	hexasc		#convert in asc code
	nop
	move	$s0, $v0	#31
	POP	($a0)
	
	move	$s1, $a1
	andi	$s1, $s1, 0xF00 #get 3rd bit of a1 : 6
	srl	$s1, $s1, 8	
	PUSH	($a0)
	move	$a0, $s1	#store it in a0, the input arg for hexasc
	jal 	hexasc		#convert in asc code
	nop
	move	$s1, $v0	#36
	POP	($a0)
	
	move	$s2, $a1
	andi	$s2, $s2, 0xF0	#get 2nd bit of a1 : 5
	srl	$s2, $s2, 4	
	PUSH	($a0)
	move	$a0, $s2	#store it in a0, the input arg for hexasc
	jal 	hexasc		#convert in asc code
	nop
	move	$s2, $v0	#35
	POP	($a0)
	
	move	$s3, $a1
	andi	$s3, $s3, 0xF	#get 1rst bit of a1 : 3
	srl	$s3, $s3, 0	
	PUSH	($a0)
	move	$a0, $s3	#store it in a0, the input arg for hexasc
	jal 	hexasc		#convert in asc code
	nop
	move	$s3, $v0	#33
	POP	($a0)
	
	addi	$s4, $0, 58	# the semi colon in t4
	
	sll	$s2,$s2,24
	sll	$s4,$s4,16
	sll	$s1, $s1,8
	add	$t5, $s2, $s4
	or	$t5, $t5, $s1
	or	$t5, $t5, $s0
	
	sw	$t5, 0($a0)
	sw	$s3, 4($a0)

	    	
	#recuperating the saved registers
	POP	($s4)
	POP	($s3)
	POP	($s2)
	POP	($s1)
	POP	($s0)
	POP	($t5)
	POP	($t4)
	POP	($t3)
	POP	($t2)
	POP	($t1)
	POP	($t0)
	POP	($ra)
	
	jr	$ra
	nop
