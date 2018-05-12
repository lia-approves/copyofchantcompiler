#### Start of IR ####

# S1:  a = 2
# S2:  t1 = 2 + 2

#### End of IR ####


#### Start of Assembly ####

.global main
.text
main:

#### Start of Statements ####

statementnumber_1:

push $2
pop (a)

statementnumber_2:

push $2
push $2
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
  ret
format:
  .asciz  "%d\n"

.data
a:
  .quad  0

#### End of Assembly ####
