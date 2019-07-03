loadi	r0,0
store	r0,0
loadi	r1,0
store	r1,1
L0:
load	r2,0
loadi	r3,10
cmpr	r2,r3
jgt	L1
load	r0,1
add	r0,0
store	r0,1
load	r1,0
addi	r1,1
store	r1,0
jmp	L0
L1:
load	r2,1
writed	r2
loadi r3,'\n'
writec r3
halt
