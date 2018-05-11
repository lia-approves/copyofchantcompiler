#### Start of Assembly ####

.global main
.text
main:

#### Start of Statements ####

statementnumber_1:

push $2
pop (a)

statementnumber_2:

push (a)
push $10
pop %rax
pop %rbx
cmp %rax, %rbx
jl statementnumber_4

statementnumber_3:

jmp statementnumber_6

statementnumber_4:

push $3
pop (b)

statementnumber_5:

jmp statementnumber_7

statementnumber_6:

push $4
pop (b)

statementnumber_7:

push (a)
push (b)
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
b:
  .quad  0

#### End of Assembly ####
