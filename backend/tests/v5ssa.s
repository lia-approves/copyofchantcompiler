#### Start of IR ####
#S1:	program begin
#S2:	t0 = &a
#S3:	t1 = 13
#S4:	t2 = 14
#S5:	t3 = t1 + t2
#S6:	*t0 = t3
#S7:	t4 = &b
#S8:	t5 = 13
#S9:	t6 = 14
#S10:	t7 = t5 + t6
#S11:	*t4 = t7
#S12:	t8 = a
#S13:	return t8
#S14:	program end
#### END of IR ####


statementnumber_1:
#### Start of Assembly ####
#### Start of Statements ####
.global main
.text
 main:
mov %rsp, %rbp
sub $16, %rsp

statementnumber_2:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_3:
push $13

statementnumber_4:
push $14

statementnumber_5:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

statementnumber_6:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_7:
mov %rbp,%rcx
sub $16, %rcx
push %rcx

statementnumber_8:
push $13

statementnumber_9:
push $14

statementnumber_10:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

statementnumber_11:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_12:
mov %rbp,%rcx
sub $8, %rcx
push (%rcx)

statementnumber_13:
#program prints ae

statementnumber_14:
#### End of Statements ####
pop %rax
GDB_ENDPROG_BREAKPOINT:
mov $format, %rdi
mov %rax, %rsi
mov $0, %rax
call printf

##DESTROY LOCAL VARS
add $16, %rsp
##END DESTROY LOCAL VARS

mov $0, %rax
ret
format:
.asciz  "%d\n"

#### End of Assembly ####
