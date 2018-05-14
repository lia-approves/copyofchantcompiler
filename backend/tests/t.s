#PARAMS: 3
#### Start of IR ####

# S0:  print
/*###BEGIN FUNct DEF###*/
# S1:  print
/*.type foo, @function
foo:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
*/
# S2:  print
/*push $45
*/
# S3:  a = 45
# S4:  print
/*push 16(%rbp)
*/
# S5:  print
/*push $8
*/
# S6:  t1 = bob + 8
# S7:  bob = t1
# S8:  print
/*push $45
*/
# S9:  h = 45
# S10:  print
/*push $45
*/
# S11:  j = 45
# S12:  print
/*push $45
*/
# S13:  mike = 45
# S14:  print
/*push $45
*/
# S15:  ab = 45
# S16:  print
/*push 16(%rbp)
*/
# S17:  print
/*push $5
*/
# S18:  t2 = bob + 5
# S19:  print
/*pop %rax
mov %rbp, %rsp
pop %rbp
ret*/
# S20:  print
/*###END FUN DEF###*/
# S21:  print
/*.global main
.text
main:
mov %rsp, %rbp*/
# S22:  alloc 8*3 bytes:
# S23:  print
/*push $9
*/
# S24:  y = 9
# S25:  print
/*push $1
*/
# S26:  x = 1
# S27:  print
/*push $17
*/
# S28:  print
/*push $17
*/
# S29:  print
/*push $17
*/
# S30:  print
/*call foo
*/
# S31:  print
/*push %rax
*/
# S32:  print
/*pop -24(%rbp)
*/
# S33:  print
/*add $24, %rsp
*/
# S34:  print
/*push $12
*/
# S35:  print
/*push -24(%rbp)
*/
# S36:  t3 = 12 + foo_retval

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
