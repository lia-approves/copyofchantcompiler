
#### Start of Assembly ####

.global main
.text
main:

###

mov $12, %rax
mov $0, %rdi
syscall

push %rax
call fun
pop %rax

add $8, %rax

push %rax
call fun
pop %rax

mov %rax, %rdi
mov $12, %rax
syscall

push %rax
call fun
pop %rax

movq $4, (%rax)


  ret

format:
  .asciz  "%d\n"

fun:
  mov     $format, %rdi
  mov     %rax, %rsi
  xor     %rax, %rax
  call    printf
  ret

.data

#### End of Assembly ####
