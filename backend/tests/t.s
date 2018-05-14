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
/*push 16(%rbp)
*/
# S9:  print
/*push $5
*/
# S10:  t2 = bob + 5
# S11:  print
/*pop %rax
mov %rbp, %rsp
pop %rbp
ret*/
# S12:  print
/*###END FUN DEF###*/
# S13:  print
/*.global main
.text
main:
mov %rsp, %rbp*/
# S14:  alloc 8*3 bytes:
# S15:  print
/*push $9
*/
# S16:  y = 9
# S17:  print
/*push $1
*/
# S18:  x = 1
# S19:  print
/*push $17
*/
# S20:  print
/*call foo
*/
# S21:  print
/*push %rax
*/
# S22:  print
/*pop -24(%rbp)
*/
# S23:  print
/*add $8, %rsp
*/
# S24:  print
/*push $12
*/
# S25:  print
/*push -24(%rbp)
*/
# S26:  t3 = 12 + foo_retval

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

push 16(%rbp)


statementnumber_9:

push $5


statementnumber_10:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_11:

pop %rax
mov %rbp, %rsp
pop %rbp
ret

statementnumber_12:

###END FUN DEF###

statementnumber_13:

.global main
.text
main:
mov %rsp, %rbp

statementnumber_14:

sub $24, %rsp

statementnumber_15:

push $9


statementnumber_16:

pop -8(%rbp)

statementnumber_17:

push $1


statementnumber_18:

pop -16(%rbp)

statementnumber_19:

push $17


statementnumber_20:

call foo


statementnumber_21:

push %rax


statementnumber_22:

pop -24(%rbp)


statementnumber_23:

add $8, %rsp


statementnumber_24:

push $12


statementnumber_25:

push -24(%rbp)


statementnumber_26:

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
