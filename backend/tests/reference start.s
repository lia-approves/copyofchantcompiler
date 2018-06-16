#### Start of IR ####

#S1:	func begin foo
#S2:	t1 = 1
#S3:	a = t1
#S4:	t2 = p1
#S5:	t3 = 1
#S6:	t4 = t2 + t3
#S7:	return t4
#S8:	func end foo
#S9:	program begin
#S10:	t5 = 3
#S11:	t6 = 2
#S12:	t7 = t5 * t6
#S13:	param t7
#S14:	call foo,1  --> foo_retval
#S15:	t8 = foo_retval
#S16:	return t8

#### End of IR ####


#### Start of Assembly ####

#### Start of Statements ####

statementnumber_1:

.type foo,@function
foo:
push %rbp
mov %rsp, %rbp
sub $1, %rsp
statementnumber_2:

push $1

statementnumber_3:

pop -8(%rbp)

statementnumber_4:

push 16(%rbp)

statementnumber_5:

push $1

statementnumber_6:

pop %rax
pop %rbx
add %rax, %rbx
push %rbx
statementnumber_7:


statementnumber_8:

pop %rax
mov %rbp, %rsp
pop %rbp
ret

statementnumber_9:

.global main
.text
main:
mov %rsp, %rbp
sub $8, %rsp
statementnumber_10:



mov $12,%rax # brk syscall number
mov $0, %rdi # 0 is invalid, want to get current position
syscall  #puts start of heap in rax
mov %rax,%rsi #save rax in rsi

mov %rax, %rdi #prepare to move allocate by moving breakpoint
add $16, %rdi #move break by 16 bytes or 2 vars
mov $12, %rax #call again
syscall #we have allocated 

#mov $12,%rax # brk syscall number
#mov $0, %rdi # 0 is invalid, want to get current position
#syscall  #puts start of current heap in rax
          #we will use original rsi for offset
#mov %rax, %rdi #prepare to move allocate by moving breakpoint
#add $16, %rdi #move break by 16 bytes or 2 vars
#mov $12, %rax #call again
#syscall #we have allocated 

mov %rsi,-8(%rbp)

push $1
pop 0(%rsi)
push $2
pop 8(%rsi)
push $3
pop 16(%rsi)
push $4
pop 45(%rsi)

push 45(%rsi)






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


/*

foo(bob){
  if(((bob<100)&&(bob>0))||((bob<=100)&&(bob>=0))) {}
  while (!(bob==0)){
    bob=bob-1
  }
  return (((12/3)-4)+(3*2))
}

main(){
  x[2]
  x[1]=42
  param x[1]
  foo_retval=foo(x[1])
  return foo_retval
}


x=tuple(2)

a=2
b=6+5

assignable extends arithExp: variable or dereferece

a,x,b,tom or c[5],x[5],bob[9]

a=5
c[5]=6+7
x[6]=b*t
x=s[4]+4*t+7
bob[9]=c[t] + 5 * y + x[4 + t]

x = tuple(4)
x[2] = tuple(6)
x = {7,tuple(6),4,7}
x[2][3]=5
x[2] = {0,0,5,0,0,0}

*/
