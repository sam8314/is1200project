  # labwork.S
  # Written 2015-2017 by F Lundevall
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

.global enable_interrupt

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

.data
.text

enable_interrupt:
    ei
    jr $ra
    nop
