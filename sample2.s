
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

sub $8, %rsp
statementnumber_statementnumber_2:

push %rbp
push $-16
pop %rax
pop %rbx
add %rax, %rbx
push %rbx
pop %rax
mov -8(%rbp), %rbx
mov %rbx, (%rax)
add $24, -8(%rbp)
mov -8(%rbp), %rdi
mov $12, %rax
syscall

statementnumber_statementnumber_3:

push $30
push %rbp
push $-16
pop %rax
pop %rbx
add %rax, %rbx
push (%rbx)
push $2
pop %rax
imul $8, %rax
pop %rbx
add %rax, %rbx
push %rbx
pop %rax
pop (%rax)

statementnumber_statementnumber_4:

push $12
push %rbp
push $-16
pop %rax
pop %rbx
add %rax, %rbx
push (%rbx)
push $2
pop %rax
imul $8, %rax
pop %rbx
add %rax, %rbx
push (%rbx)
pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_statementnumber_5:

#### End of Statements ####

pop %rax
mov     $format, %rdi
mov     %rax, %rsi
xor     %rax, %rax
call    printf

##DESTROY LOCAL VARS
add $8, %rsp
add $8, %rsp
##end DESTROY LOCAL VARS

  ret
format:
  .asciz  "%d\n"

.data

#### End of Assembly ####
