# VARS: 2
#### Start of IR ####

# S1:  a = 5
# S2:  b = 6
# S3:  b = 9
# S4:  t1 = a + 5

#### End of IR ####


#### Start of Assembly ####
.text
.global main

#how to call:

#push $7 #param1
#push $4 #param2
#push $2 #param3
#call foo
#add $8, %rsp #after funct call
#add $8, %rsp
#add $8, %rsp or #add $24, %rsp

#result in %rax ex: push %rax

#function def w 3 param
.type	foo, @function
foo:
push %rbp
mov %rsp, %rbp
sub $8, %rsp
sub $8, %rsp   #for local vars
sub $8, %rsp   #or: sub $24, %rsp
push 16(%rbp)
push 24(%rbp)
pop %rax
pop %rbx
add %rbx, %rax

#1st param 16(%rbp)
#2nd param 24(%rbp)
#3rd param 32(%rbp)
#1st local var  -8(%rbp)
#2nd local var -16(%rbp)
#3rd local var -24(%rbp)

#mov $4,%rax #body, store return value in %rax

mov %rbp, %rsp
pop %rbp
ret


main:
##allocation of local vars
mov %rsp, %rbp
sub $16, %rsp
##end allocation

#### Start of Statements ####

statementnumber_1:

push $5
pop -8(%rbp)

statementnumber_2:

push $6
pop -16(%rbp)

statementnumber_3:

push $9
pop -16(%rbp)

statementnumber_4:

push -8(%rbp)
push $5
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

#### End of Statements ####
add $8, %rsp

push $15 #3rd
push $12 #2nd
push $18 #1st
call foo
add $8, %rsp
add $8, %rsp
add $8, %rsp

push %rax
pop %rax
mov     $format, %rdi
mov     %rax, %rsi
xor     %rax, %rax
call    printf

##DESTROY LOCAL VARS
 add $16,%rsp
##end destroy local vars
ret
format:
  .asciz  "%d\n"

.data
a:
  .quad  0
b:
  .quad  0

#### End of Assembly ####

