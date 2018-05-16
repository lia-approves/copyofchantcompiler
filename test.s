/*#### Start of IR ####

# S0:  ###BEGIN FUNct DEF###
# S1:  .type foo, @function
foo:
push %rbp
mov %rsp, %rbp
sub $0, %rsp

# S2:  push 16(%rbp)

# S3:  push $100

# S4:  if (bob < 100) goto S6:
# S5:  goto S9:
# S6:  push 16(%rbp)

# S7:  push $0

# S8:  if (bob > 0) goto S17:
# S9:  push 16(%rbp)

# S10:  push $100

# S11:  if (bob <= 100) goto S13:
# S12:  goto S16:
# S13:  push 16(%rbp)

# S14:  push $0

# S15:  if (bob >= 0) goto S17:
# S16:  goto S18:
# S17:  goto S19:
# S18:  goto S20:
# S19:  goto S20:
# S20:  push 16(%rbp)

# S21:  push $0

# S22:  if (bob == 0) goto S24:
# S23:  goto S25:
# S24:  goto S30:
# S25:  push 16(%rbp)

# S26:  push $1

# S27:  t1 = bob - 1
# S28:  bob = t1
# S29:  goto S20:
# S30:  push $12

# S31:  push $3

# S32:  t2 = 12 / 3
# S33:  push $4

# S34:  t3 = t2 - 4
# S35:  push $3

# S36:  push $2

# S37:  t4 = 3 * 2
# S38:  t5 = t3 + t4
# S39:  pop %rax
mov %rbp, %rsp
pop %rbp
ret
# S40:  ###END FUN DEF###
# S41:  .global main
.text
main:
mov %rsp, %rbp
# S42:  alloc 8*1 bytes:
# S43:  push $42

# S44:  call foo

# S45:  push %rax

# S46:  pop -8(%rbp)

# S47:  add $8, %rsp

# S48:  push -8(%rbp)


#### End of IR ####*/


#### Start of Assembly ####

#### Start of Statements ####

statementnumber_0:

###BEGIN FUNct DEF###

statementnumber_1:

.type foo, @function
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

pop %rax
mov %rbp, %rsp
pop %rbp
ret

statementnumber_40:

###END FUN DEF###

statementnumber_41:

.global main
.text
main:
mov %rsp, %rbp

statementnumber_42:

sub $8, %rsp

statementnumber_43:

push $42


statementnumber_44:

call foo


statementnumber_45:

push %rax


statementnumber_46:

pop -8(%rbp)


statementnumber_47:

add $8, %rsp


statementnumber_48:

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
