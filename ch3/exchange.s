	.file	"exchange.c"
	.text
	.p2align 4,,15
	.globl	exchange
	.type	exchange, @function
exchange:
.LFB24:
	.cfi_startproc
	movl	4(%esp), %edx
	movl	8(%esp), %ecx
	movl	(%edx), %eax
	movl	%ecx, (%edx)
	ret
	.cfi_endproc
.LFE24:
	.size	exchange, .-exchange
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
