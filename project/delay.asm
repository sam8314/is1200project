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

    	subi 	$t0, $t0, 1
    	bne 	$t0, $zero, .delay_loop

	POP	($a0)
    	POP	($ra)              	
    	jr 	$ra	#go back to caller
    	nop