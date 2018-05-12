
# ---------------------------------------------------------------------------$# A 64-bit Linux application that writes the first 90 Fibonacci numbers.  It
# needs to be linked with a C library.
# http://cs.lmu.edu/~ray/notes/gasexamples/
# Assemble and Link:
#     gcc fib.s
# ---------------------------------------------------------------------------$
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
call malloc
push %rax
movq $5, (%rsp)
movq $6, 8(%rsp)
movq $-1, 16(%rsp)
movq 16(%rsp), %rax

pop %rbx
mov     $format, %rdi
mov     %rax, %rsi
xor     %rax, %rax
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

