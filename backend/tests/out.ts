#### Start of IR ####
#S1:	program begin
#S2:	t0 = &a
#S3:	t1 = 4
#S4:	*t0 = t1
#S5:	t2 = &b
#S6:	t3 = 5
#S7:	*t2 = t3
#S8:	t4 = &c
#S9:	t5 = 5
#S10:	*t4 = newTuple(t5)
#S11:	t6 = &c
#S12:	t7 = 3
#S13:	t8 = &t6[t7]
#S14:	t9 = 6
#S15:	*t8 = t9
#S16:	t10 = x
#S17:	return t10
#S18:	program end
#### END of IR ####


statementnumber_1:
#### Start of Assembly ####
#### Start of Statements ####
.global main
.text
 main:
mov %rsp, %rbp
sub $24, %rsp

statementnumber_2:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_3:
push $4

statementnumber_4:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_5:
mov %rbp,%rcx
sub $16, %rcx
push %rcx

statementnumber_6:
push $5

statementnumber_7:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_8:
mov %rbp,%rcx
sub $24, %rcx
push %rcx

statementnumber_9:
push $5

statementnumber_10:
#new tuple
mov $12, %rax
mov $0, %rdi
syscall
mov %rax, %rsi
mov %rax, %rdi
pop %rax
inc %rax
mov $8, %rbx
imul %rax, %rbx
add %rbx, %rdi
mov $12, %rax
syscall
pop %rcx
mov %rsi, (%rcx)

statementnumber_11:
mov %rbp,%rcx
sub $24, %rcx
push %rcx

statementnumber_12:
push $3

statementnumber_13:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_14:
push $6

statementnumber_15:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_16:
mov %rbp,%rcx
sub $32, %rcx
push (%rcx)

statementnumber_17:
#program prints ae

statementnumber_18:
#### End of Statements ####
pop %rax
GDB_ENDPROG_BREAKPOINT:
mov $format, %rdi
mov %rax, %rsi
mov $0, %rax
call printf

##DESTROY LOCAL VARS
add $24, %rsp
##END DESTROY LOCAL VARS

mov $0, %rax
ret
format:
.asciz  "%d\n"

#### End of Assembly ####
