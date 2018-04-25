
# ---------------------------------------------------------------------------$# A 64-bit Linux application that writes the first 90 Fibonacci numbers.  It
# needs to be linked with a C library.
# http://cs.lmu.edu/~ray/notes/gasexamples/
# Assemble and Link:
#     gcc fib.s
# ---------------------------------------------------------------------------$
        .global main

        .text
main:
        mov     $4, %rax                # this will print whatever we put in rax

        mov     $format, %rdi           # set 1st parameter (format)
        mov     %rax, %rsi              # set 2nd parameter (current_number)
        xor     %rax, %rax              # because printf is varargs

        call    printf                  # printf(format, current_number)

        ret

format:
        .asciz  "%20ld\n"
