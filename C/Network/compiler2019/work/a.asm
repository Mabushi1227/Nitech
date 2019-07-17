loadi	r0,1
store	r0,0
loadi	r1,100
store	r1,6
L0:
load	r2,0
load	r3,6
cmpr	r2,r3
jgt	L1
loadi	r0,1
store	r0,1
loadi	r1,0
store	r1,2
L2:
load	r2,1
load	r3,0
cmpr	r2,r3
jgt	L3
load	r0,0
load	r1,1
divr	r0,r1
store	r0,3
load	r2,3
load	r3,1
mulr	r2,r3
store	r2,5
load	r0,0
load	r1,5
subr	r0,r1
store	r0,4
load	r2,4
loadi	r3,0
cmpr	r2,r3
jnz	L4
load	r0,2
loadi	r1,1
addr	r0,r1
store	r0,2
L4:
load	r2,1
loadi	r3,1
addr	r2,r3
store	r2,1
jmp	L2
L3:
load	r0,2
loadi	r1,2
cmpr	r0,r1
jnz	L6
load	r2,0
writed	r2
loadi r3,'\n'
writec r3
L6:
load	r0,0
loadi	r1,1
addr	r0,r1
store	r0,0
jmp	L0
L1:
halt
