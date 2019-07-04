   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
5156                     ; 4 	void delay(u16 time)
5156                     ; 5 {
5158                     	switch	.text
5159  0000               _delay:
5161  0000 89            	pushw	x
5162       00000000      OFST:	set	0
5165  0001               L1143:
5166                     ; 6 	while(time--);
5168  0001 1e01          	ldw	x,(OFST+1,sp)
5169  0003 1d0001        	subw	x,#1
5170  0006 1f01          	ldw	(OFST+1,sp),x
5171  0008 1c0001        	addw	x,#1
5172  000b a30000        	cpw	x,#0
5173  000e 26f1          	jrne	L1143
5174                     ; 7 }
5177  0010 85            	popw	x
5178  0011 81            	ret
5191                     	xdef	_delay
5210                     	end
