	.file	"stack.c"
	.globl	globalx
	.data
	.align 4
	.type	globalx, @object
	.size	globalx, 4
globalx:
	.long	12
	.section	.rodata
	.align 4
.LC0:
	.string	"address of function print's localx=%p\n"
	.text
	.globl	print
	.type	print, @function
print:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$0, -12(%ebp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	print, .-print
	.section	.rodata
	.align 4
.LC1:
	.string	"address of function main's localx=%p\n"
	.align 4
.LC2:
	.string	"address of function main's localy=%p\n"
.LC3:
	.string	"address of globalx=%p\n"
.LC4:
	.string	"address of mallocx=%p\n"
.LC5:
	.string	"address of print=%p\n"
.LC6:
	.string	"pid = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	movl	$0, 20(%esp)
	movl	$2, 24(%esp)
	movl	$4, (%esp)
	call	malloc
	movl	%eax, 28(%esp)
	leal	20(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	leal	24(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC2, (%esp)
	call	printf
	movl	$globalx, 4(%esp)
	movl	$.LC3, (%esp)
	call	printf
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC4, (%esp)
	call	printf
	movl	$print, 4(%esp)
	movl	$.LC5, (%esp)
	call	printf
	call	print
	call	getpid
	movl	%eax, 4(%esp)
	movl	$.LC6, (%esp)
	call	printf
.L3:
	jmp	.L3
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
