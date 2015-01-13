	.file	"main.c"
	.globl	buf
	.data
	.align 4
	.type	buf, @object
	.size	buf, 8
buf:
	.long	1
	.long	2
	.section	.rodata
	.align 4
.LC0:
	.string	"before swap buf[0] = %d, buf[1] = %d\n"
	.align 4
.LC1:
	.string	"after swap buf[0] = %d, buf[1] = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	movl	buf+4, %edx
	movl	buf, %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	call	swap
	movl	buf+4, %edx
	movl	buf, %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
