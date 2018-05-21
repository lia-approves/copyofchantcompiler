.global main

.text

main:
## create a tuple x(3)
## x->1 = 1
## x->2 = 2
## x->3 = 3

push %rbp
mov %rsp, %rbp
push $33
mov (%rsp), %rax
movq $3, %rdi

mov $0x2d, %rax
mov $0, %rbx
syscall

mov %rax, %rcx
push %rcx
add $16, %rcx
movq $5, (%rsp)
movq $6, 8(%rsp)
movq $-1, 16(%rsp)
movq 8(%rsp), %rax

push %rcx
add $24, %rcx
movq $1, (%rsp)
movq $2, 8(%rsp)
movq $3, 16(%rsp)
movq 8(%rsp), %rax

pop %rbx
mov     $format, %rdi
mov     %rax, %rsi
xor     %rax, %rax
pop	%rbx
pop	%rbx
pop	%rbx
call    printf
  ret

fun:
  add $3, %rbx
  ret

format:
  .asciz  "%0ld\n"

.data
a:
  .quad  0
