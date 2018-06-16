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
# S2:  t1 = bob + 8
# S3:  bob = t1
# S4:  a = 45
# S5:  t2 = bob + 5
# S6:  print
/*pop %rax
mov %rbp, %rsp
pop %rbp
ret*/
# S7:  print
/*###END FUN DEF###*/
# S8:  print
/*.global main
.text
main:
mov %rsp, %rbp*/
# S9:  alloc 8*1 bytes:
# S10:  t3 = 1 + 1
# S11:  print
/*call foo
*/
# S12:  print
/*push %rax
*/
# S13:  print
/*pop -8(%rbp)
*/
# S14:  print
/*add $8, %rsp
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
push $8
pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_3:

pop 16(%rbp)

statementnumber_4:

push $45
pop -8(%rbp)

statementnumber_5:

push 16(%rbp)
push $5
pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_6:

pop %rax
mov %rbp, %rsp
pop %rbp
ret

statementnumber_7:

###END FUN DEF###

statementnumber_8:

.global main
.text
main:
mov %rsp, %rbp

statementnumber_9:

sub $8, %rsp

statementnumber_10:

push $1
push $1
pop %rax
pop %rbx
add %rax, %rbx
push %rbx


statementnumber_11:

call foo


statementnumber_12:

push %rax


statementnumber_13:

pop -8(%rbp)


statementnumber_14:

add $8, %rsp

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
