# run on Linux with
# gcc -c add.s && ld add.o && ./a.out

      .global _start

      .text
_start:
      push    $3
      push    $2
      pop     %ax
      pop     %bx
      add     %ax, %bx
      pop     %ax

      # exit(0)
      mov     $60, %rax               # system call 60 is exit
      xor     %rdi, %rdi              # we want return code 0
      syscall                         # invoke operating system to exit
