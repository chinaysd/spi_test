   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
5088                     	bsct
5089  0000               _dataIndex:
5090  0000 00            	dc.b	0
5168                     ; 8 main()
5168                     ; 9 {
5170                     	switch	.text
5171  0000               _main:
5173  0000 88            	push	a
5174       00000001      OFST:	set	1
5177                     ; 11 	IO_init();
5179  0001 cd0000        	call	_IO_init
5181                     ; 13 	SPI_MasterInit();
5183  0004 cd0000        	call	_SPI_MasterInit
5185                     ; 15 	for(i=0;i<8;i++)
5187  0007 0f01          	clr	(OFST+0,sp)
5188  0009               L7043:
5189                     ; 17 		Data[i]=~(0x01<<i);
5191  0009 7b01          	ld	a,(OFST+0,sp)
5192  000b 5f            	clrw	x
5193  000c 97            	ld	xl,a
5194  000d 7b01          	ld	a,(OFST+0,sp)
5195  000f 905f          	clrw	y
5196  0011 9097          	ld	yl,a
5197  0013 a601          	ld	a,#1
5198  0015 905d          	tnzw	y
5199  0017 2705          	jreq	L6
5200  0019               L01:
5201  0019 48            	sll	a
5202  001a 905a          	decw	y
5203  001c 26fb          	jrne	L01
5204  001e               L6:
5205  001e 43            	cpl	a
5206  001f e700          	ld	(_Data,x),a
5207                     ; 15 	for(i=0;i<8;i++)
5209  0021 0c01          	inc	(OFST+0,sp)
5212  0023 7b01          	ld	a,(OFST+0,sp)
5213  0025 a108          	cp	a,#8
5214  0027 25e0          	jrult	L7043
5215  0029               L5143:
5216                     ; 21 		if(dataIndex==8)
5218  0029 b600          	ld	a,_dataIndex
5219  002b a108          	cp	a,#8
5220  002d 2606          	jrne	L1243
5221                     ; 23 		dataIndex=0;
5223  002f 3f00          	clr	_dataIndex
5224                     ; 24 		SPI_CR2|=0x10;//通知SPI接口发送完当前这个最后一个数据后发送CRC校验寄存器中的校验码
5226  0031 72185201      	bset	_SPI_CR2,#4
5227  0035               L1243:
5228                     ; 28 		PB_ODR=Data[dataIndex];
5230  0035 b600          	ld	a,_dataIndex
5231  0037 5f            	clrw	x
5232  0038 97            	ld	xl,a
5233  0039 e600          	ld	a,(_Data,x)
5234  003b c75005        	ld	_PB_ODR,a
5236  003e               L7243:
5237                     ; 30 		while((SPI_SR&0x02)==0);
5239  003e c65203        	ld	a,_SPI_SR
5240  0041 a502          	bcp	a,#2
5241  0043 27f9          	jreq	L7243
5242                     ; 32 		SPI_DR=Data[dataIndex++];
5244  0045 b600          	ld	a,_dataIndex
5245  0047 97            	ld	xl,a
5246  0048 3c00          	inc	_dataIndex
5247  004a 9f            	ld	a,xl
5248  004b 5f            	clrw	x
5249  004c 97            	ld	xl,a
5250  004d e600          	ld	a,(_Data,x)
5251  004f c75204        	ld	_SPI_DR,a
5252                     ; 33 		delay(50000);
5254  0052 aec350        	ldw	x,#50000
5255  0055 cd0000        	call	_delay
5258  0058 20cf          	jra	L5143
5292                     	xdef	_main
5293                     	xdef	_dataIndex
5294                     	switch	.ubsct
5295  0000               _Data:
5296  0000 000000000000  	ds.b	8
5297                     	xdef	_Data
5298                     	xref	_IO_init
5299                     	xref	_SPI_MasterInit
5300                     	xref	_delay
5320                     	end
