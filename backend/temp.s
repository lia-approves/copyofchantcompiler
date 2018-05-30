#### Start of Assembly ####

mov $0x2d, %rax
mov $0, %rbx
syscall
mov %rax, %rsi
#### Start of Statements ####

statementnumber_1:

.global main
.text
main:
mov %rsp, %rbp
sub $16, %rsp
statementnumber_2:

push $12
mov %rbp, %rax
add $-8, %rax
push %rax
pop %rax
pop (%rax)

statementnumber_3:

mov %rbp, %rax
add $-16, %rax
push %rax
pop %rax
mov %rsi, (%rax)
add $24, %rsi

statementnumber_4:

#push $3
#pop %rax
#pop (%rax)

statementnumber_5:

mov %rbp, %rax
add $-8, %rax
push (%rax)
push $30
pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_6:

#### End of Statements ####

pop %rax
mov     $format, %rdi
mov     %rax, %rsi
xor     %rax, %rax
call    printf

##DESTROY LOCAL VARS
add $16, %rsp
##end DESTROY LOCAL VARS

  ret
format:
  .asciz  "%d\n"

.data

#### End of Assembly ####
