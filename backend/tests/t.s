/*#### Start of IR ####

# S1:	func begin foo
# S2:	t1 = bob
# S3:	t2 = 100
# S4:	if (t1 < t2) goto S6:
# S5:	goto S9:
# S6:	t3 = bob
# S7:	t4 = 0
# S8:	if (t3 > t4) goto S17:
# S9:	t5 = bob
# S10:	t6 = 100
# S11:	if (t5 <= t6) goto S13:
# S12:	goto S16:
# S13:	t7 = bob
# S14:	t8 = 0
# S15:	if (t7 >= t8) goto S17:
# S16:	goto S18:
# S17:	goto S19:
# S18:	goto S20:
# S19:	goto S20:
# S20:	t9 = bob
# S21:	t10 = 0
# S22:	if (t9 == t10) goto S24:
# S23:	goto S25:
# S24:	goto S30:
# S25:	t11 = bob
# S26:	t12 = 1
# S27:	t13 = t11 - t12
# S28:	bob = t13
# S29:	goto S20:
# S30:	t14 = 12
# S31:	t15 = 3
# S32:	t16 = t14 / t15
# S33:	t17 = 4
# S34:	t18 = t16 - t17
# S35:	t19 = 3
# S36:	t20 = 2
# S37:	t21 = t19 * t20
# S38:	t22 = t18 + t21
# S39:	return t22
# S40:	func end foo
# S41:	Program Start
# S42:	t23 = 42
# S43:	call foo,1  --> foo_retval
# S44:	t24 = foo_retval

#### End of IR ####*/


#### Start of Assembly ####

#### Start of Statements ####

statementnumber_1:

.type foo,@function
foo:
push %rbp
mov %rsp, %rbp
sub $0, %rsp
statementnumber_2:

push 16(%rbp)

statementnumber_3:

push $100

statementnumber_4:

pop %rax
pop %rbx
cmp %rax, %rbx
jl statementnumber_6

statementnumber_5:

jmp statementnumber_9

statementnumber_6:

push 16(%rbp)

statementnumber_7:

push $0

statementnumber_8:

pop %rax
pop %rbx
cmp %rax, %rbx
jg statementnumber_17

statementnumber_9:

push 16(%rbp)

statementnumber_10:

push $100

statementnumber_11:

pop %rax
pop %rbx
cmp %rax, %rbx
jle statementnumber_13

statementnumber_12:

jmp statementnumber_16

statementnumber_13:

push 16(%rbp)

statementnumber_14:

push $0

statementnumber_15:

pop %rax
pop %rbx
cmp %rax, %rbx
jge statementnumber_17

statementnumber_16:

jmp statementnumber_18

statementnumber_17:

jmp statementnumber_19

statementnumber_18:

jmp statementnumber_20

statementnumber_19:

jmp statementnumber_20

statementnumber_20:

push 16(%rbp)

statementnumber_21:

push $0

statementnumber_22:

pop %rax
pop %rbx
cmp %rax, %rbx
je statementnumber_24

statementnumber_23:

jmp statementnumber_25

statementnumber_24:

jmp statementnumber_30

statementnumber_25:

push 16(%rbp)

statementnumber_26:

push $1

statementnumber_27:

pop %rax
pop %rbx
sub %rax, %rbx
push %rbx


statementnumber_28:

pop 16(%rbp)

statementnumber_29:

jmp statementnumber_20

statementnumber_30:

push $12

statementnumber_31:

push $3

statementnumber_32:

pop %rbx
pop %rax
mov $0, %rdx
idiv %rbx
push %rax


statementnumber_33:

push $4

statementnumber_34:

pop %rax
pop %rbx
sub %rax, %rbx
push %rbx


statementnumber_35:

push $3

statementnumber_36:

push $2

statementnumber_37:

pop %rax
pop %rbx
imul %rax, %rbx
push %rbx


statementnumber_38:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_39:


statementnumber_40:

pop %rax
mov %rbp, %rsp
pop %rbp
ret

statementnumber_41:

.global main
.text
main:
mov %rsp, %rbp
sub $8, %rsp
statementnumber_42:

push $42

statementnumber_43:

call foo
push %rax
pop -8(%rbp)
add $8, %rsp

statementnumber_44:

push -8(%rbp)
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
