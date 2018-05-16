#### Start of Assembly ####

#### Start of Statements ####

statementnumber_0:

###BEGIN FUNct DEF###

statementnumber_1:

.type foo, @function
foo:
push %rbp
mov %rsp, %rbp
sub $32, %rsp


statementnumber_2:

push $45


statementnumber_3:

pop -8(%rbp)

statementnumber_4:

push 16(%rbp)


statementnumber_5:

push $8


statementnumber_6:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_7:

pop 16(%rbp)

statementnumber_8:

push $45


statementnumber_9:

pop -16(%rbp)

statementnumber_10:

push $45


statementnumber_11:

pop -24(%rbp)

statementnumber_12:

push $45


statementnumber_13:

pop 32(%rbp)

statementnumber_14:

push $45


statementnumber_15:

pop -32(%rbp)

statementnumber_16:

push 16(%rbp)


statementnumber_17:

push $5


statementnumber_18:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_19:

pop %rax
mov %rbp, %rsp
pop %rbp
ret

statementnumber_20:

###END FUN DEF###

statementnumber_21:

.global main
.text
main:
mov %rsp, %rbp

statementnumber_22:

sub $24, %rsp

statementnumber_23:

push $9


statementnumber_24:

pop -8(%rbp)

statementnumber_25:

push $1


statementnumber_26:

pop -16(%rbp)

statementnumber_27:

push $17


statementnumber_28:

push $17


statementnumber_29:

push $17


statementnumber_30:

call foo


statementnumber_31:

push %rax


statementnumber_32:

pop -24(%rbp)


statementnumber_33:

add $24, %rsp


statementnumber_34:

push $12


statementnumber_35:

push -24(%rbp)


statementnumber_36:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx

#### End of Statements ####

pop %rax
mov     $format, %rdi
mov     %rax, %rsi
xor     %rax, %rax
call    printf

##DESTROY LOCAL VARS
add $24, %rsp
##end DESTROY LOCAL VARS

  ret
format:
  .asciz  "%d\n"

.data

#### End of Assembly ####
