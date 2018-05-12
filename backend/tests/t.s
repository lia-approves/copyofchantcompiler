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
/*push 16(%rbp)
*/
# S4:  print
/*push $8
*/
# S5:  t1 = bob + 8
# S6:  bob = t1
# S7:  print
/*push $45
*/
# S8:  a = 45
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
# S15:  alloc 8*1 bytes:
# S16:  print
/*push $1
*/
# S17:  print
/*push $1
*/
# S18:  t3 = 1 + 1
# S19:  print
/*call foo
*/
# S20:  print
/*push %rax
*/
# S21:  print
/*pop -8(%rbp)
*/
# S22:  print
/*add $8, %rsp
*/
# S23:  print
/*push $12
*/

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

push 16(%rbp)


statementnumber_4:

push $8


statementnumber_5:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_6:

pop 16(%rbp)

statementnumber_7:

push $45


statementnumber_8:

pop -8(%rbp)

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

sub $8, %rsp

statementnumber_16:

push $1


statementnumber_17:

push $1


statementnumber_18:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_19:

call foo


statementnumber_20:

push %rax


statementnumber_21:

pop -8(%rbp)


statementnumber_22:

add $8, %rsp


statementnumber_23:

push $12

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
