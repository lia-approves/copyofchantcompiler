
### Live variable info for graphID: 0 ###

# Variable assignment for variable bob at:29,

# Global Variables: bob,
# Phi functions to be placed at:24,

### End of  variable info for graphID: 0 ###


### Live variable info for graphID: 46 ###

# Variable assignment for variable x at:46,55,

# Variable assignment for variable y at:46,55,

# Global Variables: x,y,
# Phi functions to be placed at:51,

### End of  variable info for graphID: 46 ###

## CONTROL FLOW GRAPH BEGIN ##
## Program Flow starts at "main program end "##
# __________________
# Block Id: 0
# Block Start Statements:
#   S0:  func begin foo
#   S1:  param bob
#   S2:  t1 = bob0
#   S3:  t2 = 100
#   S4:  if (t1 < t2) goto S6:
# Block End 
# Outgoing Edges -> {True: 6,False: 5}
# __________________

# __________________
# Block Id: 5
# Incoming Edges ->{0} 
# Block Start Statements:
#   S5:  goto S9:
# Block End 
# Outgoing Edges -> {9}
# __________________

# __________________
# Block Id: 6
# Incoming Edges ->{0} 
# Block Start Statements:
#   S6:  t3 = bob0
#   S7:  t4 = 0
#   S8:  if (t3 > t4) goto S17:
# Block End 
# Outgoing Edges -> {True: 17,False: 9}
# __________________

# __________________
# Block Id: 9
# Incoming Edges ->{5,6} 
# Block Start Statements:
#   S9:  t5 = bob2
#   S10:  t6 = 100
#   S11:  if (t5 <= t6) goto S13:
# Block End 
# Outgoing Edges -> {True: 13,False: 12}
# __________________

# __________________
# Block Id: 12
# Incoming Edges ->{9} 
# Block Start Statements:
#   S12:  goto S16:
# Block End 
# Outgoing Edges -> {16}
# __________________

# __________________
# Block Id: 13
# Incoming Edges ->{9} 
# Block Start Statements:
#   S13:  t7 = bob2
#   S14:  t8 = 0
#   S15:  if (t7 >= t8) goto S17:
# Block End 
# Outgoing Edges -> {True: 17,False: 16}
# __________________

# __________________
# Block Id: 16
# Incoming Edges ->{12,13} 
# Block Start Statements:
#   S16:  goto S18:
# Block End 
# Outgoing Edges -> {18}
# __________________

# __________________
# Block Id: 17
# Incoming Edges ->{6,13} 
# Block Start Statements:
#   S17:  goto S19:
# Block End 
# Outgoing Edges -> {19}
# __________________

# __________________
# Block Id: 18
# Incoming Edges ->{16} 
# Block Start Statements:
#   S18:  goto S22:
# Block End 
# Outgoing Edges -> {22}
# __________________

# __________________
# Block Id: 19
# Incoming Edges ->{17} 
# Block Start Statements:
#   S19:  t9 = 4
#   S20:  a1 = t9
#   S21:  goto S24:
# Block End 
# Outgoing Edges -> {24}
# __________________

# __________________
# Block Id: 22
# Incoming Edges ->{18} 
# Block Start Statements:
#   S22:  t10 = 5
#   S23:  b1 = t10
# Block End 
# Outgoing Edges -> {24}
# __________________

# __________________
# Block Id: 24
# Incoming Edges ->{19,30,22} 
# Block Start Statements:
#   S24:  bob1 = phi( bob0 bob2 bob2)
#   S25:  t11 = bob1
#   S26:  t12 = 0
#   S27:  if (t11 == t12) goto S29:
# Block End 
# Outgoing Edges -> {True: 29,False: 28}
# __________________

# __________________
# Block Id: 28
# Incoming Edges ->{24} 
# Block Start Statements:
#   S28:  goto S30:
# Block End 
# Outgoing Edges -> {30}
# __________________

# __________________
# Block Id: 29
# Incoming Edges ->{24} 
# Block Start Statements:
#   S29:  goto S35:
# Block End 
# Outgoing Edges -> {35}
# __________________

# __________________
# Block Id: 30
# Incoming Edges ->{28} 
# Block Start Statements:
#   S30:  t13 = bob1
#   S31:  t14 = 1
#   S32:  t15 = t13 - t14
#   S33:  bob2 = t15
#   S34:  goto S24:
# Block End 
# Outgoing Edges -> {24}
# __________________

# __________________
# Block Id: 35
# Incoming Edges ->{29} 
# Block Start Statements:
#   S35:  t16 = 12
#   S36:  t17 = 3
#   S37:  t18 = t16 / t17
#   S38:  t19 = 4
#   S39:  t20 = t18 - t19
#   S40:  t21 = 3
#   S41:  t22 = 2
#   S42:  t23 = t21 * t22
#   S43:  t24 = t20 + t23
#   S44:  return t24
#   S45:  func end foo
# Block End 
# __________________

# __________________
# Block Id: 46
# Block Start Statements:
#   S46:  main program begin
#   S47:  t25 = 1
#   S48:  x1 = t25
#   S49:  t26 = 1
#   S50:  y1 = t26
# Block End 
# Outgoing Edges -> {51}
# __________________

# __________________
# Block Id: 51
# Incoming Edges ->{57,46} 
# Block Start Statements:
#   S51:  y2 = phi( y1 y3)
#   S52:  x2 = phi( x1 x3)
#   S53:  t27 = x2
#   S54:  t28 = 100
#   S55:  if (t27 < t28) goto S57:
# Block End 
# Outgoing Edges -> {True: 57,False: 56}
# __________________

# __________________
# Block Id: 56
# Incoming Edges ->{51} 
# Block Start Statements:
#   S56:  goto S70:
# Block End 
# Outgoing Edges -> {70}
# __________________

# __________________
# Block Id: 57
# Incoming Edges ->{51} 
# Block Start Statements:
#   S57:  t29 = x2
#   S58:  t30 = 1
#   S59:  t31 = t29 + t30
#   S60:  x3 = t31
#   S61:  t32 = y2
#   S62:  t33 = x3
#   S63:  t34 = t32 + t33
#   S64:  y3 = t34
#   S65:  t35 = 1
#   S66:  t36 = 1
#   S67:  t37 = t35 + t36
#   S68:  z1 = t37
#   S69:  goto S51:
# Block End 
# Outgoing Edges -> {51}
# __________________

# __________________
# Block Id: 70
# Incoming Edges ->{56} 
# Block Start Statements:
#   S70:  t38 = &x
#   S71:  t39 = 2
#   S72:  *t38 = newTuple(t39)
#   S73:  t40 = 13
#   S74:  t41 = &x
#   S75:  t42 = 1
#   S76:  t43 = &t41[t42]
#   S77:  *t43 = t40
#   S78:  t44 = &x
#   S79:  t45 = 1
#   S80:  t46 = t44[t45]
#   S81:  argument t46
#   S82:  call foo,1  --> foo_retval1
#   S83:  t47 = &x
#   S84:  t48 = 7
#   S85:  t49 = t47[t48]
#   S86:  return t49
#   S87:  main program end
# Block End 
# __________________

## CONTROL FLOW GRAPH ENDOF ##

# ______________________
# Domination Info for Graph id: 0
# BlockId: 0, iDom: -1, Dominates: 0,6,17,24,9,5,19,29,28,35,30,13,16,12,18,22, Dominance Frontier: 
# BlockId: 6, iDom: 0, Dominates: 6, Dominance Frontier: 17,9,
# BlockId: 17, iDom: 0, Dominates: 17,19, Dominance Frontier: 24,
# BlockId: 19, iDom: 17, Dominates: 19, Dominance Frontier: 24,
# BlockId: 24, iDom: 0, Dominates: 24,29,28,35,30, Dominance Frontier: 24,
# BlockId: 29, iDom: 24, Dominates: 29,35, Dominance Frontier: 
# BlockId: 35, iDom: 29, Dominates: 35, Dominance Frontier: 
# BlockId: 28, iDom: 24, Dominates: 28,30, Dominance Frontier: 24,
# BlockId: 30, iDom: 28, Dominates: 30, Dominance Frontier: 24,
# BlockId: 9, iDom: 0, Dominates: 9,13,16,12,18,22, Dominance Frontier: 17,24,
# BlockId: 13, iDom: 9, Dominates: 13, Dominance Frontier: 17,16,
# BlockId: 16, iDom: 9, Dominates: 16,18,22, Dominance Frontier: 24,
# BlockId: 18, iDom: 16, Dominates: 18,22, Dominance Frontier: 24,
# BlockId: 22, iDom: 18, Dominates: 22, Dominance Frontier: 24,
# BlockId: 12, iDom: 9, Dominates: 12, Dominance Frontier: 16,
# BlockId: 5, iDom: 0, Dominates: 5, Dominance Frontier: 9,

# ______________________
# Domination Info for Graph id: 46
# BlockId: 46, iDom: -1, Dominates: 46,51,57,56,70, Dominance Frontier: 
# BlockId: 51, iDom: 46, Dominates: 51,57,56,70, Dominance Frontier: 51,
# BlockId: 57, iDom: 51, Dominates: 57, Dominance Frontier: 51,
# BlockId: 56, iDom: 51, Dominates: 56,70, Dominance Frontier: 
# BlockId: 70, iDom: 56, Dominates: 70, Dominance Frontier: 

S0:
.type foo,@function
foo:
push %rbp
mov %rsp, %rbp
sub $16, %rsp
S1:
#parameter bob

S2:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

S3:
push $100

S4:
pop %rax
pop %rbx
cmp %rax, %rbx
jl S6

S5:
jmp S9

S6:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

S7:
push $0

S8:
pop %rax
pop %rbx
cmp %rax, %rbx
jg S17

S9:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

S10:
push $100

S11:
pop %rax
pop %rbx
cmp %rax, %rbx
jle S13

S12:
jmp S16

S13:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

S14:
push $0

S15:
pop %rax
pop %rbx
cmp %rax, %rbx
jge S17

S16:
jmp S18

S17:
jmp S19

S18:
jmp S22

S19:
push $4

S20:
mov %rbp,%rcx
sub $8, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S21:
jmp S24

S22:
push $5

S23:
mov %rbp,%rcx
sub $16, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S24:

S25:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

S26:
push $0

S27:
pop %rax
pop %rbx
cmp %rax, %rbx
je S29

S28:
jmp S30

S29:
jmp S35

S30:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

S31:
push $1

S32:
pop %rax
pop %rbx
sub %rax, %rbx
push %rbx

S33:
mov %rbp,%rcx
add $16 ,%rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S34:
jmp S24

S35:
push $12

S36:
push $3

S37:
pop %rbx
pop %rax
mov $0, %rdx
idiv %rbx
push %rax

S38:
push $4

S39:
pop %rax
pop %rbx
sub %rax, %rbx
push %rbx

S40:
push $3

S41:
push $2

S42:
pop %rax
pop %rbx
imul %rax, %rbx
push %rbx

S43:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

S44:
# Function or Program Returns Value

S45:
pop %rax
mov %rbp, %rsp
pop %rbp
ret

S46:
.global main
.text
 main:
mov %rsp, %rbp
sub $32, %rsp

S47:
push $1

S48:
mov %rbp,%rcx
sub $8, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S49:
push $1

S50:
mov %rbp,%rcx
sub $16, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S51:

S52:

S53:
mov %rbp,%rcx
sub $8, %rcx
push (%rcx)

S54:
push $100

S55:
pop %rax
pop %rbx
cmp %rax, %rbx
jl S57

S56:
jmp S70

S57:
mov %rbp,%rcx
sub $8, %rcx
push (%rcx)

S58:
push $1

S59:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

S60:
mov %rbp,%rcx
sub $8, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S61:
mov %rbp,%rcx
sub $16, %rcx
push (%rcx)

S62:
mov %rbp,%rcx
sub $8, %rcx
push (%rcx)

S63:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

S64:
mov %rbp,%rcx
sub $16, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S65:
push $1

S66:
push $1

S67:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

S68:
mov %rbp,%rcx
sub $24, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S69:
jmp S51

S70:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

S71:
push $2

S72:
#new tuple
mov $12, %rax
mov $0, %rdi
syscall
mov %rax, %rsi
mov %rax, %rdi
pop %rax
inc %rax
mov $8, %rbx
imul %rax, %rbx
add %rbx, %rdi
mov $12, %rax
syscall
pop %rcx
mov %rsi, (%rcx)

S73:
push $13

S74:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

S75:
push $1

S76:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

S77:
pop %rax
pop %rbx
mov %rbx, (%rax)

S78:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

S79:
push $1

S80:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

S81:
#argument

S82:
call foo
push %rax
pop -32(%rbp)
add $8, %rsp

S83:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

S84:
push $7

S85:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

S86:
# Function or Program Returns Value

S87:
pop %rax
mov $format, %rdi
mov %rax, %rsi
mov $0, %rax
call printf

add $32, %rsp
mov $0, %rax
ret
format:
.asciz  "%d\n"
