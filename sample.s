
#### Start of Assembly ####

.global main
.text
main:
mov %rsp, %rbp
mov $0x2d, %rax
mov $0, %rbx
syscall
mov %rax, -8(%rbp)
sub $8, %rsp
#### Start of Statements ####

statementnumber_statementnumber_1:

sub $8, %rsp
statementnumber_statementnumber_2:

push $12
push %rbp
push $-8
pop %rax
pop %rbx
add %rax, %rbx
push %rbx
pop %rax
pop (%rax)

statementnumber_statementnumber_3:

push $12
push $30
pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_statementnumber_4:

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
