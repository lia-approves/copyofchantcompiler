#PARAMS: 1
#### Start of IR ####

# S0:  print
/*###BEGIN FUNct DEF###*/
# S1:  print
/*.type foo, @function
foo:
push %rbp
mov %rsp, %rbp
sub $8, %rsp
*/
# S2:  print
/*push 16(%rbp)
*/
# S3:  print
/*push $45
*/
# S4:  a = 45
# S5:  print
/*push 16(%rbp)
*/
# S6:  print
/*push $8
*/
# S7:  t1 = bob + 8
# S8:  bob = t1
# S9:  print
/*push 16(%rbp)
*/
# S10:  print
/*push $5
*/
# S11:  t2 = bob + 5
# S12:  print
/*pop %rax
mov %rbp, %rsp
pop %rbp
ret*/
# S13:  print
/*###END FUN DEF###*/
# S14:  print
/*.global main
.text
main:
mov %rsp, %rbp*/
# S15:  alloc 8*3 bytes:
# S16:  print
/*push $9
*/
# S17:  y = 9
# S18:  print
/*push $1
*/
# S19:  x = 1
# S20:  print
/*push $17
*/
# S21:  print
/*call foo
*/
# S22:  print
/*push %rax
*/
# S23:  print
/*pop -24(%rbp)
*/
# S24:  print
/*add $8, %rsp
*/
# S25:  print
/*push $12
*/
# S26:  print
/*push -24(%rbp)
*/
# S27:  t3 = 12 + foo_retval

#### End of IR ####


#### Start of Assembly ####

#### Start of Statements ####

statementnumber_0:

###BEGIN FUNct DEF###

statementnumber_1:

.type foo, @function
foo:
push %rbp
mov %rsp, %rbp
sub $8, %rsp


statementnumber_2:

push 16(%rbp)


statementnumber_3:

push $45


statementnumber_4:

pop -8(%rbp)

statementnumber_5:

push 16(%rbp)


statementnumber_6:

push $8


statementnumber_7:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_8:

pop 16(%rbp)

statementnumber_9:

push 16(%rbp)


statementnumber_10:

push $5


statementnumber_11:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_12:

pop %rax
mov %rbp, %rsp
pop %rbp
ret

statementnumber_13:

###END FUN DEF###

statementnumber_14:

.global main
.text
main:
mov %rsp, %rbp

statementnumber_15:

sub $24, %rsp

statementnumber_16:

push $9


statementnumber_17:

pop -8(%rbp)

statementnumber_18:

push $1


statementnumber_19:

pop -16(%rbp)

statementnumber_20:

push $17


statementnumber_21:

call foo


statementnumber_22:

push %rax


statementnumber_23:

pop -24(%rbp)


statementnumber_24:

add $8, %rsp


statementnumber_25:

push $12


statementnumber_26:

push -24(%rbp)


statementnumber_27:

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
