
# ---------------------------------------------------------------------------$# A 64-bit Linux application that writes the first 90 Fibonacci numbers.  It
# needs to be linked with a C library.
# http://cs.lmu.edu/~ray/notes/gasexamples/
# Assemble and Link:
#     gcc fib.s
# ---------------------------------------------------------------------------$
.global main

.text

main:

push $3
movq $11, (a)
push (a)
pop %rax
pop %rbx
call fun
add %rax, %rbx
push %rbx

pop %rax
mov     $format, %rdi
mov     %rax, %rsi
xor     %rax, %rax
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
