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
load	r3,2
addr	r2,r3
load	r0,3
mulr	r2,r0
load	r1,L5
L5: data 100000
divr	r2,r1
load	r2,L7
L7: data 100000
mulr	r2,r2
subr	r3,r2
store	r3,1
load	r3,1
loadi	r0,10
divr	r3,r0
store	r3,1
load	r1,1
loadi	r2,10
divr	r1,r2
store	r1,6
load	r3,1
load	r0,2
addr	r3,r0
load	r1,3
mulr	r3,r1
load	r2,1
load	r3,2
addr	r2,r3
load	r0,3
mulr	r2,r0
load	r1,L9
L9: data 100000
divr	r2,r1
load	r2,L11
L11: data 100000
mulr	r2,r2
subr	r3,r2
store	r3,1
load	r3,1
loadi	r0,10
divr	r3,r0
store	r3,1
load	r1,1
loadi	r2,10
divr	r1,r2
store	r1,7
load	r3,6
load	r1,6
mulr	r3,r1
load	r2,7
load	r3,7
mulr	r2,r3
addr	r3,r2
load	r0,L15
L15: data 1000000
cmpr	r3,r0
jge	L10
load	r0,5
loadi	r1,1
addr	r0,r1
store	r0,5
L10:
load	r2,0
loadi	r3,1
addr	r2,r3
store	r2,0
jmp	L0
L1:
load	r0,5
loadi	r1,4
mulr	r0,r1
store	r0,4
writed	r0
loadi r2,'\n'
writec r2
halt
