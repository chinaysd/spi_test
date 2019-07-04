   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
5148                     ; 11 void BUS_16M(void)
5148                     ; 12 {
5150                     	switch	.text
5151  0000               _BUS_16M:
5155                     ; 14 	CLK_SWCR |= 0x02; //¿ªÆôÇÐ»»
5157  0000 721250c5      	bset	_CLK_SWCR,#1
5158                     ; 15 	CLK_SWR = 0xb4;
5160  0004 35b450c4      	mov	_CLK_SWR,#180
5162  0008               L5043:
5163                     ; 16 	while((CLK_SWCR & 0x01) == 0x01);
5165  0008 c650c5        	ld	a,_CLK_SWCR
5166  000b a401          	and	a,#1
5167  000d a101          	cp	a,#1
5168  000f 27f7          	jreq	L5043
5169                     ; 17 	CLK_CKDIVR = 0x00; //1·ÖÆµ
5171  0011 725f50c6      	clr	_CLK_CKDIVR
5172                     ; 18 	CLK_SWCR &= (~0x02); //¹Ø±ÕÇÐ»»
5174  0015 721350c5      	bres	_CLK_SWCR,#1
5175                     ; 19 }
5178  0019 81            	ret
5230                     ; 21 void Delay1ms(unsigned int time)
5230                     ; 22 {
5231                     	switch	.text
5232  001a               _Delay1ms:
5234  001a 89            	pushw	x
5235  001b 5204          	subw	sp,#4
5236       00000004      OFST:	set	4
5239                     ; 24 	for (i=0; i<time; i++)
5241  001d 5f            	clrw	x
5242  001e 1f01          	ldw	(OFST-3,sp),x
5244  0020 201a          	jra	L3443
5245  0022               L7343:
5246                     ; 26 		for (j=0; j<1000; j++)
5248  0022 5f            	clrw	x
5249  0023 1f03          	ldw	(OFST-1,sp),x
5250  0025               L7443:
5251                     ; 28 			_asm("nop");_asm("nop");
5254  0025 9d            nop
5259  0026 9d            nop
5261                     ; 26 		for (j=0; j<1000; j++)
5263  0027 1e03          	ldw	x,(OFST-1,sp)
5264  0029 1c0001        	addw	x,#1
5265  002c 1f03          	ldw	(OFST-1,sp),x
5268  002e 1e03          	ldw	x,(OFST-1,sp)
5269  0030 a303e8        	cpw	x,#1000
5270  0033 25f0          	jrult	L7443
5271                     ; 24 	for (i=0; i<time; i++)
5273  0035 1e01          	ldw	x,(OFST-3,sp)
5274  0037 1c0001        	addw	x,#1
5275  003a 1f01          	ldw	(OFST-3,sp),x
5276  003c               L3443:
5279  003c 1e01          	ldw	x,(OFST-3,sp)
5280  003e 1305          	cpw	x,(OFST+1,sp)
5281  0040 25e0          	jrult	L7343
5282                     ; 31 }
5285  0042 5b06          	addw	sp,#6
5286  0044 81            	ret
5330                     ; 33 void Delay1us(unsigned int time)
5330                     ; 34 {
5331                     	switch	.text
5332  0045               _Delay1us:
5334  0045 89            	pushw	x
5335  0046 89            	pushw	x
5336       00000002      OFST:	set	2
5339                     ; 36 	for (i=0; i<time; i++)
5341  0047 5f            	clrw	x
5342  0048 1f01          	ldw	(OFST-1,sp),x
5344  004a 2008          	jra	L3053
5345  004c               L7743:
5346                     ; 38 		_asm("nop");
5349  004c 9d            nop
5351                     ; 36 	for (i=0; i<time; i++)
5353  004d 1e01          	ldw	x,(OFST-1,sp)
5354  004f 1c0001        	addw	x,#1
5355  0052 1f01          	ldw	(OFST-1,sp),x
5356  0054               L3053:
5359  0054 1e01          	ldw	x,(OFST-1,sp)
5360  0056 1303          	cpw	x,(OFST+1,sp)
5361  0058 25f2          	jrult	L7743
5362                     ; 40 }
5365  005a 5b04          	addw	sp,#4
5366  005c 81            	ret
5379                     	xdef	_Delay1us
5380                     	xdef	_Delay1ms
5381                     	xdef	_BUS_16M
5400                     	end
