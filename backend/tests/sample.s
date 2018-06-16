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
push 8(%rbp)

statementnumber_3:
push 16(%rbp)

statementnumber_4:
push $5

statementnumber_5:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

statementnumber_6:
pop 8(%rbp)
statementnumber_7:
push 8(%rbp)

statementnumber_8:
push $5

statementnumber_9:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

statementnumber_10:
pop %rax
mov %rbp, %rsp
pop %rbp
ret
statementnumber_11:
###END FUN DEF###
statementnumber_12:
.global main
.text
main:
mov %rsp, %rbp

statementnumber_13:
add $8, %rsp
statementnumber_14:
push 8(%rbp)

statementnumber_15:
push $12

statementnumber_16:
pop 8(%rbp)
statementnumber_17:
push $12

statementnumber_18:
call foo

statementnumber_19:
push %rax

statementnumber_20:
pop 16(%rbp)

statementnumber_21:
add $8, %rsp

statementnumber_22:
push 16(%rbp)

statementnumber_23:
push $20

statementnumber_24:
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
add $16, %rsp
##end DESTROY LOCAL VARS

  ret
format:
  .asciz  "%d\n"

.data

#### End of Assembly ####
