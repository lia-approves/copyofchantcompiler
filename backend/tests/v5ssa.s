#### Start of IR ####
#S1:	func begin foo
#S2:	param bob
#S3:	t1 = bob
#S4:	t2 = 100
#S5:	if (t1 < t2) goto S7:
#S6:	goto S10:
#S7:	t3 = bob
#S8:	t4 = 0
#S9:	if (t3 > t4) goto S18:
#S10:	t5 = bob
#S11:	t6 = 100
#S12:	if (t5 <= t6) goto S14:
#S13:	goto S17:
#S14:	t7 = bob
#S15:	t8 = 0
#S16:	if (t7 >= t8) goto S18:
#S17:	goto S19:
#S18:	goto S20:
#S19:	goto S21:
#S20:	goto S21:
#S21:	t9 = bob
#S22:	t10 = 0
#S23:	if (t9 == t10) goto S25:
#S24:	goto S26:
#S25:	goto S32:
#S26:	t11 = &bob
#S27:	t12 = bob
#S28:	t13 = 1
#S29:	t14 = t12 - t13
#S30:	*t11 = t14
#S31:	goto S21:
#S32:	t15 = 12
#S33:	t16 = 3
#S34:	t17 = t15 / t16
#S35:	t18 = 4
#S36:	t19 = t17 - t18
#S37:	t20 = 3
#S38:	t21 = 2
#S39:	t22 = t20 * t21
#S40:	t23 = t19 + t22
#S41:	return t23
#S42:	func end foo
#S43:	program begin
#S44:	t24 = &x
#S45:	t25 = 2
#S46:	*t24 = newTuple(t25)
#S47:	t26 = &x
#S48:	t27 = 1
#S49:	t28 = &t26[t27]
#S50:	t29 = 13
#S51:	*t28 = t29
#S52:	t30 = &x
#S53:	t31 = 1
#S54:	t32 = t30[t31]
#S55:	argument t32
#S56:	call foo,1  --> foo_retval
#S57:	t33 = &x
#S58:	t34 = 20
#S59:	*t33 = newTuple(t34)
#S60:	t35 = &x
#S61:	t36 = 0
#S62:	t37 = &t35[t36]
#S63:	t38 = 2
#S64:	*t37 = t38
#S65:	t39 = &x
#S66:	t40 = 1
#S67:	t41 = &t39[t40]
#S68:	t42 = 3
#S69:	*t41 = t42
#S70:	t43 = &x
#S71:	t44 = 4
#S72:	t45 = &t43[t44]
#S73:	t46 = 3
#S74:	*t45 = t46
#S75:	t47 = &x
#S76:	t48 = 5
#S77:	t49 = &t47[t48]
#S78:	t50 = 1
#S79:	*t49 = t50
#S80:	t51 = &x
#S81:	t52 = 6
#S82:	t53 = &t51[t52]
#S83:	t54 = 5
#S84:	*t53 = newTuple(t54)
#S85:	t55 = &x
#S86:	t56 = 6
#S87:	t57 = &t55[t56]
#S88:	t58 = 4
#S89:	t59 = &t57[t58]
#S90:	t60 = 14
#S91:	*t59 = t60
#S92:	t61 = &x
#S93:	t62 = 9
#S94:	t63 = &t61[t62]
#S95:	t64 = 2
#S96:	*t63 = t64
#S97:	t65 = &x
#S98:	t66 = 8
#S99:	t67 = &t65[t66]
#S100:	t68 = 4
#S101:	*t67 = t68
#S102:	t69 = &x
#S103:	t70 = 11
#S104:	t71 = &t69[t70]
#S105:	t72 = 22
#S106:	*t71 = t72
#S107:	t73 = &x
#S108:	t74 = 14
#S109:	t75 = &t73[t74]
#S110:	t76 = 15
#S111:	*t75 = t76
#S112:	t77 = &x
#S113:	t78 = &x
#S114:	t79 = 11
#S115:	t80 = t78[t79]
#S116:	t81 = &x
#S117:	t82 = 14
#S118:	t83 = t81[t82]
#S119:	t84 = t80 - t83
#S120:	t85 = &t77[t84]
#S121:	t86 = &x
#S122:	t87 = &x
#S123:	t88 = 0
#S124:	t89 = t87[t88]
#S125:	t90 = &x
#S126:	t91 = 1
#S127:	t92 = t90[t91]
#S128:	t93 = t89 * t92
#S129:	t94 = &t86[t93]
#S130:	t95 = &x
#S131:	t96 = &x
#S132:	t97 = 8
#S133:	t98 = t96[t97]
#S134:	t99 = t95[t98]
#S135:	t100 = &x
#S136:	t101 = 5
#S137:	t102 = t100[t101]
#S138:	t103 = t99 + t102
#S139:	t104 = t94[t103]
#S140:	t105 = &x
#S141:	t106 = 9
#S142:	t107 = t105[t106]
#S143:	t108 = t104 / t107
#S144:	*t85 = t108
#S145:	t109 = &x
#S146:	t110 = 7
#S147:	t111 = t109[t110]
#S148:	return t111
#S149:	program end
#### END of IR ####


statementnumber_1:
.type foo,@function
foo:
push %rbp
mov %rsp, %rbp
sub $0, %rsp
statementnumber_2:
#parameter bob

statementnumber_3:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_4:
push $100

statementnumber_5:
pop %rax
pop %rbx
cmp %rax, %rbx
jl statementnumber_7

statementnumber_6:
jmp statementnumber_10

statementnumber_7:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_8:
push $0

statementnumber_9:
pop %rax
pop %rbx
cmp %rax, %rbx
jg statementnumber_18

statementnumber_10:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_11:
push $100

statementnumber_12:
pop %rax
pop %rbx
cmp %rax, %rbx
jle statementnumber_14

statementnumber_13:
jmp statementnumber_17

statementnumber_14:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_15:
push $0

statementnumber_16:
pop %rax
pop %rbx
cmp %rax, %rbx
jge statementnumber_18

statementnumber_17:
jmp statementnumber_19

statementnumber_18:
jmp statementnumber_20

statementnumber_19:
jmp statementnumber_21

statementnumber_20:
jmp statementnumber_21

statementnumber_21:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_22:
push $0

statementnumber_23:
pop %rax
pop %rbx
cmp %rax, %rbx
je statementnumber_25

statementnumber_24:
jmp statementnumber_26

statementnumber_25:
jmp statementnumber_32

statementnumber_26:
mov %rbp,%rcx
add $16 ,%rcx
push %rcx

statementnumber_27:
mov %rbp,%rcx
add $16 ,%rcx
push (%rcx)

statementnumber_28:
push $1

statementnumber_29:
pop %rax
pop %rbx
sub %rax, %rbx
push %rbx

statementnumber_30:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_31:
jmp statementnumber_21

statementnumber_32:
push $12

statementnumber_33:
push $3

statementnumber_34:
pop %rbx
pop %rax
mov $0, %rdx
idiv %rbx
push %rax

statementnumber_35:
push $4

statementnumber_36:
pop %rax
pop %rbx
sub %rax, %rbx
push %rbx

statementnumber_37:
push $3

statementnumber_38:
push $2

statementnumber_39:
pop %rax
pop %rbx
imul %rax, %rbx
push %rbx

statementnumber_40:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

statementnumber_41:
#program prints ae

statementnumber_42:
pop %rax
mov %rbp, %rsp
pop %rbp
ret

statementnumber_43:
#### Start of Assembly ####
#### Start of Statements ####
.global main
.text
 main:
mov %rsp, %rbp
sub $16, %rsp

statementnumber_44:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_45:
push $2

statementnumber_46:
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

statementnumber_47:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_48:
push $1

statementnumber_49:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_50:
push $13

statementnumber_51:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_52:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_53:
push $1

statementnumber_54:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_55:
#argument

statementnumber_56:
call foo
push %rax
pop -16(%rbp)
add $8, %rsp

statementnumber_57:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_58:
push $20

statementnumber_59:
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

statementnumber_60:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_61:
push $0

statementnumber_62:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_63:
push $2

statementnumber_64:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_65:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_66:
push $1

statementnumber_67:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_68:
push $3

statementnumber_69:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_70:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_71:
push $4

statementnumber_72:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_73:
push $3

statementnumber_74:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_75:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_76:
push $5

statementnumber_77:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_78:
push $1

statementnumber_79:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_80:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_81:
push $6

statementnumber_82:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_83:
push $5

statementnumber_84:
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

statementnumber_85:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_86:
push $6

statementnumber_87:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_88:
push $4

statementnumber_89:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_90:
push $14

statementnumber_91:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_92:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_93:
push $9

statementnumber_94:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_95:
push $2

statementnumber_96:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_97:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_98:
push $8

statementnumber_99:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_100:
push $4

statementnumber_101:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_102:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_103:
push $11

statementnumber_104:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_105:
push $22

statementnumber_106:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_107:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_108:
push $14

statementnumber_109:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_110:
push $15

statementnumber_111:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_112:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_113:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_114:
push $11

statementnumber_115:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_116:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_117:
push $14

statementnumber_118:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_119:
pop %rax
pop %rbx
sub %rax, %rbx
push %rbx

statementnumber_120:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_121:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_122:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_123:
push $0

statementnumber_124:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_125:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_126:
push $1

statementnumber_127:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_128:
pop %rax
pop %rbx
imul %rax, %rbx
push %rbx

statementnumber_129:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push %rax

statementnumber_130:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_131:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_132:
push $8

statementnumber_133:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_134:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_135:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_136:
push $5

statementnumber_137:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_138:
pop %rax
pop %rbx
add %rax, %rbx
push %rbx

statementnumber_139:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_140:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_141:
push $9

statementnumber_142:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_143:
pop %rbx
pop %rax
mov $0, %rdx
idiv %rbx
push %rax

statementnumber_144:
pop %rbx
pop %rax
mov %rbx, (%rax)

statementnumber_145:
mov %rbp,%rcx
sub $8, %rcx
push %rcx

statementnumber_146:
push $7

statementnumber_147:
pop %rax
mov $8, %rbx
imul %rax, %rbx
pop %rcx
mov (%rcx), %rax
add %rbx,%rax
push (%rax)

statementnumber_148:
#program prints ae

statementnumber_149:
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

mov $0, %rax
ret
format:
.asciz  "%d\n"

#### End of Assembly ####
