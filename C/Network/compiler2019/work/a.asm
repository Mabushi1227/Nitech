loadi	r2,0
loadr	r0,r2
loadi	r2,0
loadr	r1,r2
L0:
loadr	r2,r0
loadi	r3,10
cmpr	r2,r3
jgt	L1
loadr	r2,r1
addr	r2,r0
loadr	r1,r2
loadr	r2,r0
addi	r2,1
loadr	r0,r2
jmp	L0
L1:
writed	r1
loadi r2,'\n'
writec r2
halt
