	.global	v0
	.section	.sdata
	.align	2
	.type	v0, @object
	.size	v0, 4
v0:
	.word	0
	.text
	.align	2
	.global	main
	.type	main, @function
main:
	addi 	sp,sp,-16
	sw  	ra,12(sp)
	li	s0,10
	lui 	s10,%hi(v0)
	add 	s10,s10,%lo(v0)
	sw  	s0,0(s10)
	li	a0,0
	lw  	ra,12(sp)
	addi	sp,sp,16
	jr  	ra
	li	a0,0
	lw  	ra,12(sp)
	addi	sp,sp,16
	jr  	ra
	.size	main, .-main
