## CONTROL FLOW GRAPH BEGIN ##
## Program Flow starts at "main program end "##
# __________________
# Block Id: 0
# Block Start Statements:
#   S0:  main program begin
#   S1:  t0 = 1
#   S2:  x = t0
#   S3:  t1 = 2
#   S4:  y = t1
# Block End 
# Outgoing Edges -> {5}
# __________________

# __________________
# Block Id: 5
# Incoming Edges ->{9,0} 
# Block Start Statements:
#   S5:  t2 = x
#   S6:  t3 = 100
#   S7:  if (t2 < t3) goto S9:
# Block End 
# Outgoing Edges -> {True: 9,False: 8}
# __________________

# __________________
# Block Id: 8
# Incoming Edges ->{5} 
# Block Start Statements:
#   S8:  goto S18:
# Block End 
# Outgoing Edges -> {18}
# __________________

# __________________
# Block Id: 9
# Incoming Edges ->{5} 
# Block Start Statements:
#   S9:  t4 = x
#   S10:  t5 = 1
#   S11:  t6 = t4 + t5
#   S12:  x = t6
#   S13:  t7 = y
#   S14:  t8 = x
#   S15:  t9 = t7 + t8
#   S16:  y = t9
#   S17:  goto S5:
# Block End 
# Outgoing Edges -> {5}
# __________________

# __________________
# Block Id: 18
# Incoming Edges ->{8} 
# Block Start Statements:
#   S18:  t10 = x
#   S19:  return t10
#   S20:  main program end
# Block End 
# __________________

## CONTROL FLOW GRAPH ENDOF ##

# ______________________
# Domination Info for Graph id: 0
# BlockId: 0, iDom: -1, Dominates: 0,5,9,8,18, Dominance Frontier: 
# BlockId: 5, iDom: 0, Dominates: 5,9,8,18, Dominance Frontier: 5,
# BlockId: 9, iDom: 5, Dominates: 9, Dominance Frontier: 5,
# BlockId: 8, iDom: 5, Dominates: 8,18, Dominance Frontier: 
# BlockId: 18, iDom: 8, Dominates: 18, Dominance Frontier: 

### Live variable info for graphID: 0 ###

# Variable assignment for variable x at:0,9,
# Variable assignment for variable y at:0,9,
# Global Variables: x,y,
# Phi functions to be placed at:5,

### End of  variable info for graphID: 0 ###

#   S0:  main program begin
#   S1:  t0 = 1
#   S2:  x = t0
#   S3:  t1 = 2
#   S4:  y = t1
#   S5:  y = phi(y, y)
#   S6:  x = phi(x, x)
#   S7:  t2 = x
#   S8:  t3 = 100
#   S9:  if (t2 < t3) goto S11:
#   S10:  goto S20:
#   S11:  t4 = x
#   S12:  t5 = 1
#   S13:  t6 = t4 + t5
#   S14:  x = t6
#   S15:  t7 = y
#   S16:  t8 = x
#   S17:  t9 = t7 + t8
#   S18:  y = t9
#   S19:  goto S7:
#   S20:  t10 = x
#   S21:  return t10
#   S22:  main program end

S0:
.global main
.text
 main:
mov %rsp, %rbp
sub $16, %rsp

S1:
push $1

S2:
mov %rbp,%rcx
sub $8, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S3:
push $2

S4:
mov %rbp,%rcx
sub $16, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S5:

S6:

S7:
mov %rbp,%rcx
sub $8, %rcx
push (%rcx)

S8:
push $100

S9:
pop %rax
pop %rbx
cmp %rax, %rbx
jl S11

S10:
jmp S20

S11:
mov %rbp,%rcx
sub $8, %rcx
push (%rcx)

S12:
push $1

S13:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

S14:
mov %rbp,%rcx
sub $8, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S15:
mov %rbp,%rcx
sub $16, %rcx
push (%rcx)

S16:
mov %rbp,%rcx
sub $8, %rcx
push (%rcx)

S17:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

S18:
mov %rbp,%rcx
sub $16, %rcx
push %rcx
pop %rax
pop %rbx
mov %rbx, (%rax)

S19:
jmp S7

S20:
mov %rbp,%rcx
sub $8, %rcx
push (%rcx)

S21:
# Function or Program Returns Value

S22:
pop %rax
mov $format, %rdi
mov %rax, %rsi
mov $0, %rax
call printf

add $16, %rsp
mov $0, %rax
ret
format:
.asciz  "%d\n"
