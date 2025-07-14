	.data
.globl global1
	.align 4
global1:
	.long 0
.globl global
	.align 4
global:
	.long 0

	.text
.globl main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $400, %rsp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax, global(%rip)
	movl global(%rip), %eax
	movl %eax, -8(%rbp)
	movl -8(%rbp), %eax
	leave
	ret

