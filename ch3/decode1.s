	.file	"decode1.c"
	.text
	.p2align 4,,15
	.globl	decode1
	.type	decode1, @function
decode1:
.LFB24:
	.cfi_startproc
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	16(%esp), %eax
	movl	20(%esp), %ecx
	movl	24(%esp), %edx
	movl	(%eax), %edi
	movl	(%ecx), %esi
	movl	(%edx), %ebx
	movl	%edi, (%ecx)
	movl	%esi, (%edx)
	movl	%ebx, (%eax)
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 12
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE24:
	.size	decode1, .-decode1
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
