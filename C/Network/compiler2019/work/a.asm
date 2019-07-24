loadi	r0,0
store	r0,0
loadi	r1,0
store	r1,5
loadi	r2,3827
store	r2,1
loadi	r3,8358
store	r3,2
loadi	r0,3797
store	r0,3
L0:
load	r1,0
loadi	r2,1000
cmpr	r1,r2
jge	L1
load	r3,1
load	r0,2
addr	r3,r0
load	r1,3
mulr	r3,r1
load	r2,1
load	r0,2
addr	r2,r0
load	r1,3
mulr	r2,r1
load	r0,L5
divr	r2,r0
load	r1,L7
mulr	r2,r1
subr	r3,r2
store	r3,1
load	r3,1
loadi	r2,10
divr	r3,r2
store	r3,1
load	r0,1
loadi	r1,10
divr	r0,r1
store	r0,6
load	r3,1
load	r2,2
addr	r3,r2
load	r0,3
mulr	r3,r0
load	r1,1
load	r2,2
addr	r1,r2
load	r0,3
mulr	r1,r0
load	r2,L9
divr	r1,r2
load	r0,L11
mulr	r1,r0
subr	r3,r1
store	r3,1
load	r3,1
loadi	r1,10
divr	r3,r1
store	r3,1
load	r2,1
loadi	r0,10
divr	r2,r0
store	r2,7
load	r3,6
load	r2,6
mulr	r3,r2
load	r0,7
load	r1,7
mulr	r0,r1
addr	r3,r0
load	r1,L15
cmpr	r3,r1
jge	L10
load	r3,5
loadi	r2,1
addr	r3,r2
store	r3,5
L10:
load	r0,0
loadi	r1,1
addr	r0,r1
store	r0,0
jmp	L0
L1:
load	r3,5
loadi	r2,4
mulr	r3,r2
store	r3,4
writed	r3
loadi r0,'\n'
writec r0
halt
L5: data 100000
L7: data 100000
L9: data 100000
L11: data 100000
L15: data 1000000
