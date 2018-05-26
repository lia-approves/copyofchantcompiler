#### Start of IR ####
#S1:	func begin foo
#S2:	t1 = bob
#S3:	t2 = 100
#S4:	if (t1 < t2) goto S6:
#S5:	goto S9:
#S6:	t3 = bob
#S7:	t4 = 0
#S8:	if (t3 > t4) goto S17:
#S9:	t5 = bob
#S10:	t6 = 100
#S11:	if (t5 <= t6) goto S13:
#S12:	goto S16:
#S13:	t7 = bob
#S14:	t8 = 0
#S15:	if (t7 >= t8) goto S17:
#S16:	goto S18:
#S17:	goto S19:
#S18:	goto S20:
#S19:	goto S20:
#S20:	t9 = bob
#S21:	t10 = 0
#S22:	if (t9 == t10) goto S24:
#S23:	goto S25:
#S24:	goto S31:
#S25:	t11 = &bob
#S26:	t12 = bob
#S27:	t13 = 1
#S28:	t14 = t12 - t13
#S29:	t11 = t14
#S30:	goto S20:
#S31:	t15 = 12
#S32:	t16 = 3
#S33:	t17 = t15 / t16
#S34:	t18 = 4
#S35:	t19 = t17 - t18
#S36:	t20 = 3
#S37:	t21 = 2
#S38:	t22 = t20 * t21
#S39:	t23 = t19 + t22
#S40:	return t23
#S41:	func end foo
#S42:	program begin
#S43:	t24 = &x
#S44:	t25 = 2
#S45:	t24 = newTuple(t25)
#S46:	t26 = &x
#S47:	t27 = 1
#S48:	t28 = &[t26[t27]]
#S49:	t29 = 13
#S50:	t28 = t29
#S51:	t30 = &x
#S52:	t31 = 1
#S53:	t32 = [t30[t31]]
#S54:	param t32
#S55:	call foo,1  --> foo_retval
#S56:	t33 = &x
#S57:	t34 = 20
#S58:	t33 = newTuple(t34)
#S59:	t35 = &x
#S60:	t36 = 0
#S61:	t37 = &[t35[t36]]
#S62:	t38 = 2
#S63:	t37 = t38
#S64:	t39 = &x
#S65:	t40 = 1
#S66:	t41 = &[t39[t40]]
#S67:	t42 = 3
#S68:	t41 = t42
#S69:	t43 = &x
#S70:	t44 = 4
#S71:	t45 = &[t43[t44]]
#S72:	t46 = 3
#S73:	t45 = t46
#S74:	t47 = &x
#S75:	t48 = 5
#S76:	t49 = &[t47[t48]]
#S77:	t50 = 1
#S78:	t49 = t50
#S79:	t51 = &x
#S80:	t52 = 6
#S81:	t53 = &[t51[t52]]
#S82:	t54 = 5
#S83:	t53 = newTuple(t54)
#S84:	t55 = &x
#S85:	t56 = 6
#S86:	t57 = &[t55[t56]]
#S87:	t58 = 4
#S88:	t59 = &[t57[t58]]
#S89:	t60 = 14
#S90:	t59 = t60
#S91:	t61 = &x
#S92:	t62 = 9
#S93:	t63 = &[t61[t62]]
#S94:	t64 = 2
#S95:	t63 = t64
#S96:	t65 = &x
#S97:	t66 = 8
#S98:	t67 = &[t65[t66]]
#S99:	t68 = 4
#S100:	t67 = t68
#S101:	t69 = &x
#S102:	t70 = 11
#S103:	t71 = &[t69[t70]]
#S104:	t72 = 22
#S105:	t71 = t72
#S106:	t73 = &x
#S107:	t74 = 14
#S108:	t75 = &[t73[t74]]
#S109:	t76 = 15
#S110:	t75 = t76
#S111:	t77 = &x
#S112:	t78 = &x
#S113:	t79 = 11
#S114:	t80 = [t78[t79]]
#S115:	t81 = &x
#S116:	t82 = 14
#S117:	t83 = [t81[t82]]
#S118:	t84 = t80 - t83
#S119:	t85 = &[t77[t84]]
#S120:	t86 = &x
#S121:	t87 = &x
#S122:	t88 = 0
#S123:	t89 = [t87[t88]]
#S124:	t90 = &x
#S125:	t91 = 1
#S126:	t92 = [t90[t91]]
#S127:	t93 = t89 * t92
#S128:	t94 = &[t86[t93]]
#S129:	t95 = &x
#S130:	t96 = &x
#S131:	t97 = 8
#S132:	t98 = [t96[t97]]
#S133:	t99 = [t95[t98]]
#S134:	t100 = &x
#S135:	t101 = 5
#S136:	t102 = [t100[t101]]
#S137:	t103 = t99 + t102
#S138:	t104 = [t94[t103]]
#S139:	t105 = &x
#S140:	t106 = 9
#S141:	t107 = [t105[t106]]
#S142:	t108 = t104 / t107
#S143:	t85 = t108
#S144:	t109 = &x
#S145:	t110 = 7
#S146:	t111 = [t109[t110]]
#S147:	return t111
#S148:	program end
#### END of IR ####


statementnumber_1:
.type foo,@function
foo:
push %rbp
mov %rsp, %rbp
sub $0, %rsp
statementnumber_2:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_3:
push $100

statementnumber_4:
pop %rax
pop %rbx
cmp %rax, %rbx
jl statementnumber_6

statementnumber_5:
jmp statementnumber_9

statementnumber_6:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_7:
push $0

statementnumber_8:
pop %rax
pop %rbx
cmp %rax, %rbx
jg statementnumber_17

statementnumber_9:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_10:
push $100

statementnumber_11:
pop %rax
pop %rbx
cmp %rax, %rbx
jle statementnumber_13

statementnumber_12:
jmp statementnumber_16

statementnumber_13:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_14:
push $0

statementnumber_15:
pop %rax
pop %rbx
cmp %rax, %rbx
jge statementnumber_17

statementnumber_16:
jmp statementnumber_18

statementnumber_17:
jmp statementnumber_19

statementnumber_18:
jmp statementnumber_20

statementnumber_19:
jmp statementnumber_20

statementnumber_20:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_21:
push $0

statementnumber_22:
pop %rax
pop %rbx
cmp %rax, %rbx
je statementnumber_24

statementnumber_23:
jmp statementnumber_25

statementnumber_24:
jmp statementnumber_31

statementnumber_25:
mov %rbp,%rcx
add $16 ,%rcx
push %rcx

statementnumber_26:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_27:
push $1

statementnumber_28:
pop %rax
pop %rbx
sub %rax, %rbx
push %rbx

statementnumber_29:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_30:
jmp statementnumber_20

statementnumber_31:
push $12

statementnumber_32:
push $3

statementnumber_33:
pop %rbx
pop %rax
mov $0, %rdx
idiv %rbx
push %rax

statementnumber_34:
push $4

statementnumber_35:
pop %rax
pop %rbx
sub %rax, %rbx
push %rbx

statementnumber_36:
push $3

statementnumber_37:
push $2

statementnumber_38:
pop %rax
pop %rbx
imul %rax, %rbx
push %rbx

statementnumber_39:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

statementnumber_40:
#program prints ae

statementnumber_41:
pop %rax
mov %rbp, %rsp
pop %rbp
ret

statementnumber_42:
#### Start of Assembly ####
#### Start of Statements ####
.global main
.text
 main:
mov %rsp, %rbp
sub $16, %rsp

statementnumber_43:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_44:
push $2

statementnumber_45:
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

statementnumber_46:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_47:
push $1

statementnumber_48:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_49:
push $13

statementnumber_50:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_51:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_52:
push $1

statementnumber_53:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_54:
#Param

statementnumber_55:
call foo
push %rax
pop -16(%rbp)
add $8, %rsp

statementnumber_56:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_57:
push $20

statementnumber_58:
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

statementnumber_59:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_60:
push $0

statementnumber_61:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_62:
push $2

statementnumber_63:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_64:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_65:
push $1

statementnumber_66:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_67:
push $3

statementnumber_68:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_69:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_70:
push $4

statementnumber_71:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_72:
push $3

statementnumber_73:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_74:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_75:
push $5

statementnumber_76:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_77:
push $1

statementnumber_78:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_79:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_80:
push $6

statementnumber_81:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_82:
push $5

statementnumber_83:
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

statementnumber_84:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_85:
push $6

statementnumber_86:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_87:
push $4

statementnumber_88:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_89:
push $14

statementnumber_90:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_91:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_92:
push $9

statementnumber_93:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_94:
push $2

statementnumber_95:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_96:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_97:
push $8

statementnumber_98:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_99:
push $4

statementnumber_100:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_101:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_102:
push $11

statementnumber_103:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_104:
push $22

statementnumber_105:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_106:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_107:
push $14

statementnumber_108:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_109:
push $15

statementnumber_110:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_111:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_112:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_113:
push $11

statementnumber_114:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_115:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_116:
push $14

statementnumber_117:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_118:
pop %rax
pop %rbx
sub %rax, %rbx
push %rbx

statementnumber_119:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_120:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_121:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_122:
push $0

statementnumber_123:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_124:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_125:
push $1

statementnumber_126:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_127:
pop %rax
pop %rbx
imul %rax, %rbx
push %rbx

statementnumber_128:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_129:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_130:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_131:
push $8

statementnumber_132:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_133:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_134:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_135:
push $5

statementnumber_136:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_137:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

statementnumber_138:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_139:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_140:
push $9

statementnumber_141:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_142:
pop %rbx
pop %rax
mov $0, %rdx
idiv %rbx
push %rax

statementnumber_143:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_144:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_145:
push $7

statementnumber_146:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_147:
#program prints ae

statementnumber_148:
#### End of Statements ####
pop %rax
GDB_ENDPROG_BREAKPOINT:
mov $format, %rdi
mov %rax, %rsi
mov $0, %rax
call printf

##DESTROY LOCAL VARS
add $16, %rsp
##END DESTROY LOCAL VARS

ret
format:
.asciz  "%d\n"

.data
#### End of Assembly ####
