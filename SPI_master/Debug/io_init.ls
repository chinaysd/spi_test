   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
5145                     ; 4 void IO_init(void)
5145                     ; 5 {
5147                     	switch	.text
5148  0000               _IO_init:
5152                     ; 7 	PB_DDR = 0xff;
5154  0000 35ff5007      	mov	_PB_DDR,#255
5155                     ; 8 	PB_CR1 = 0xff;
5157  0004 35ff5008      	mov	_PB_CR1,#255
5158                     ; 9 	PB_CR2 = 0x00;
5160  0008 725f5009      	clr	_PB_CR2
5161                     ; 10 	PB_ODR = 0xff;
5163  000c 35ff5005      	mov	_PB_ODR,#255
5164                     ; 12 }
5167  0010 81            	ret
5180                     	xdef	_IO_init
5199                     	end
