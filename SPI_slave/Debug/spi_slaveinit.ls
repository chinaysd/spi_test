   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
5148                     ; 11 void SPI_SlaveInit(void)
5148                     ; 12 {
5150                     	switch	.text
5151  0000               _SPI_SlaveInit:
5155                     ; 14 	PC_DDR|=(1<<7);
5157  0000 721e500c      	bset	_PC_DDR,#7
5158                     ; 15 	PC_CR1|=(1<<5)|(1<<6)|(1<<7);
5160  0004 c6500d        	ld	a,_PC_CR1
5161  0007 aae0          	or	a,#224
5162  0009 c7500d        	ld	_PC_CR1,a
5163                     ; 20 	SPI_CR2=0x02;
5165  000c 35025201      	mov	_SPI_CR2,#2
5166                     ; 22 	SPI_ICR|=0b01100000;//开接收缓冲器非空中断，错误中断使能
5168  0010 c65202        	ld	a,_SPI_ICR
5169  0013 aa60          	or	a,#96
5170  0015 c75202        	ld	_SPI_ICR,a
5171                     ; 24 	SPI_CR2|=0x20;
5173  0018 721a5201      	bset	_SPI_CR2,#5
5174                     ; 27 	SPI_CR1|=0x40;
5176  001c 721c5200      	bset	_SPI_CR1,#6
5177                     ; 28 }
5180  0020 81            	ret
5193                     	xdef	_SPI_SlaveInit
5212                     	end
