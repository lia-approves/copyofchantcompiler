# VARS: 2
#### Start of IR ####

# S1:  a = 5
# S2:  b = 6
# S3:  b = 6
# S4:  t1 = a + 5

#### End of IR ####


#### Start of Assembly ####

.global main
.text
main:

#### Start of Statements ####

statementnumber_1:

push $5
pop (a)

statementnumber_2:

push $6
pop (b)

statementnumber_3:

push $6
pop (b)

statementnumber_4:

push (a)
push $5
pop %rax
pop %rbx
addw %rax, %rbx
push %rbx

#### End of Statements ####

pop %rax
mov     $format, %rdi
mov     %rax, %rsi
xor     %rax, %rax
call    printf
  ret
format:
  .asciz  "%d\n"

.data
a:
  .quad  0
b:
  .quad  0

#### End of Assembly ####
