	.file	"switch.c"
	.text
	.globl	switch2asm
	.type	switch2asm, @function
switch2asm:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$1, -4(%ebp)
	movl	8(%ebp), %eax
	cmpl	$1, %eax
	je	.L3
	cmpl	$1, %eax
	jl	.L2
	cmpl	$5, %eax
	jg	.L2
	jmp	.L7
.L3:
	movl	8(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, -4(%ebp)
	jmp	.L5
.L7:
	movl	8(%ebp), %eax
	addl	%eax, %eax
	leal	0(,%eax,8), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -4(%ebp)
	jmp	.L5
.L2:
	movl	$10, -4(%ebp)
.L5:
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	switch2asm, .-switch2asm
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
