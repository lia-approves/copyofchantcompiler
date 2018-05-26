#### Start of IR ####

#S1:	func begin foo
#S2:	t1 = a
#S3:	t2 = 1
#S4:	a = t2
#S5:	t3 = p1
#S6:	t4 = 1
#S7:	t5 = p1 + t4
#S8:	return t5
#S9:	func end foo
#S10:	program begin
#S11:	t6 = 3
#S12:	t7 = 2
#S13:	t8 = t6 * t7
#S14:	param t8
#S15:	call foo,1  --> foo_retval
#S16:	t9 = foo_retval
#S17:	return t9

#### End of IR ####


#### Start of Assembly ####

#### Start of Statements ####

statementnumber_1:

.type foo,@function
foo:
push %rbp
mov %rsp, %rbp
sub $1, %rsp
statementnumber_2:

push -8(%rbp)

statementnumber_3:

push $1

statementnumber_4:

pop -8(%rbp)

statementnumber_5:

push 16(%rbp)

statementnumber_6:

push $1

statementnumber_7:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_8:


statementnumber_9:

pop %rax
mov %rbp, %rsp
pop %rbp
ret

statementnumber_10:

.global main
.text
main:
mov %rsp, %rbp
sub $8, %rsp
statementnumber_11:

push $3

statementnumber_12:

push $2

statementnumber_13:

pop %rax
pop %rbx
imul %rax, %rbx
push %rbx


statementnumber_14:


statementnumber_15:

call foo
push %rax
pop -8(%rbp)
add $8, %rsp

statementnumber_16:

push -8(%rbp)

statementnumber_17:

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
