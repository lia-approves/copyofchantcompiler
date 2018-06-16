#### Start of IR ####

#S1:	program begin
#S2:	t1 = 9
#S3:	
#S4:	
#S5:	return t3

#### Start of Assembly ####

#### Start of Statements ####

statementnumber_1:

.global main
.text
main:
mov %rsp, %rbp
sub $8, %rsp

#heap operations
mov $12,%rax
mov $0, %rdi
syscall
mov %rax,%rsi
mov %rax,%rdi
add $8,%rdi
mov $12,%rax
syscall
#heap ops end

statementnumber_2:

#kpush
push $9

statementnumber_3:

mov %rbp,%rcx
sub $8, %rcx
push %rcx

pop %rax
pop %rbx

mov %rbx,(%rax)

statementnumber_4:

mov %rbp,%rcx
sub $8, %rcx
push (%rcx)

statementnumber_5:

#### End of Statements ####

pop %rax
mov     $format, %rdi
mov     %rax, %rsi
xor     %rax, %rax
call    printf

##DESTROY LOCAL VARS
add $8, %rsp
##end DESTROY LOCAL VARS

  ret
format:
  .asciz  "%d\n"

.data

#### End of Assembly ####
