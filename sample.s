
#### Start of Assembly ####

.global main
.text
main:
mov %rsp, %rbp
mov $12, %rax
mov $0, %rdi
syscall
mov %rax, -8(%rbp)
sub $8, %rsp
#### Start of Statements ####

statementnumber_statementnumber_1:

sub $16, %rsp
statementnumber_statementnumber_2:

push $12
push %rbp
push $-16
pop %rax
pop %rbx
add %rax, %rbx
push %rbx
pop %rax
pop (%rax)

statementnumber_statementnumber_3:

push %rbp
push $-24
pop %rax
pop %rbx
add %rax, %rbx
push %rbx
pop %rax
mov -8(%rbp), %rbx
mov %rbx, (%rax)
add $24, -8(%rbp)

statementnumber_statementnumber_4:

push $5
push %rbp
push $-24
pop %rax
pop %rbx
add %rax, %rbx
push %rbx
push $2
pop %rax
imul $8, %rax
pop %rbx
add %rax, %rbx
push %rbx
pop %rax
pop (%rax)

statementnumber_statementnumber_5:

push %rbp
push $-16
pop %rax
pop %rbx
add %rax, %rbx
push (%rbx)
push $30
pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_statementnumber_6:

#### End of Statements ####

pop %rax
mov     $format, %rdi
mov     %rax, %rsi
xor     %rax, %rax
call    printf

##DESTROY LOCAL VARS
add $8, %rsp
add $16, %rsp
##end DESTROY LOCAL VARS

  ret
format:
  .asciz  "%d\n"

.data

#### End of Assembly ####
