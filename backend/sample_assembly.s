# needs to be linked with a C library.
#
# Assemble and Link:
#     gcc fib.s
# ---------------------------------------------------------------------------$
        .global main

        .text
main:
        mov     $1, %ecx               # ecx will countdown to 0
        xor     %rax, %rax              # rax will hold the current number
        xor     %rbx, %rbx              # rbx will hold the next number
        inc     %rbx                    # rbx is originally 1
        add     $4, %rax                # whatever we put in rax will be printed!

        mov     $format, %rdi           # set 1st parameter (format)
        mov     %rax, %rsi              # set 2nd parameter (current_number)
        xor     %rax, %rax              # because printf is varargs

        call    printf                  # printf(format, current_number)

        ret

format:
        .asciz  "%20ld\n"
