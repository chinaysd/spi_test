   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
5088                     	bsct
5089  0000               _dataIndex:
5090  0000 00            	dc.b	0
5091  0001               _checkFlag:
5092  0001 0000          	dc.w	0
5168                     ; 8 main()
5168                     ; 9 {
5170                     	switch	.text
5171  0000               _main:
5173  0000 88            	push	a
5174       00000001      OFST:	set	1
5177                     ; 11 	IO_init();
5179  0001 cd0000        	call	_IO_init
5181                     ; 13 	SPI_SlaveInit();
5183  0004 cd0000        	call	_SPI_SlaveInit
5185                     ; 14   _asm("rim");//打开总中断，sim为关闭总中断
5188  0007 9a            rim
5191  0008               L1143:
5192                     ; 15 	while(dataIndex!=8);
5194  0008 b600          	ld	a,_dataIndex
5195  000a a108          	cp	a,#8
5196  000c 26fa          	jrne	L1143
5197                     ; 16 	for(i=0;i<8;i++)
5199  000e 0f01          	clr	(OFST+0,sp)
5200  0010               L5143:
5201                     ; 18 	if(Data[i]!=~(0x01<<i))
5203  0010 7b01          	ld	a,(OFST+0,sp)
5204  0012 5f            	clrw	x
5205  0013 97            	ld	xl,a
5206  0014 e600          	ld	a,(_Data,x)
5207  0016 5f            	clrw	x
5208  0017 97            	ld	xl,a
5209  0018 90ae0001      	ldw	y,#1
5210  001c 7b01          	ld	a,(OFST+0,sp)
5211  001e 4d            	tnz	a
5212  001f 2705          	jreq	L6
5213  0021               L01:
5214  0021 9058          	sllw	y
5215  0023 4a            	dec	a
5216  0024 26fb          	jrne	L01
5217  0026               L6:
5218  0026 9053          	cplw	y
5219  0028 90bf00        	ldw	c_y,y
5220  002b b300          	cpw	x,c_y
5221  002d 2707          	jreq	L3243
5222                     ; 20 	checkFlag++;
5224  002f be01          	ldw	x,_checkFlag
5225  0031 1c0001        	addw	x,#1
5226  0034 bf01          	ldw	_checkFlag,x
5227  0036               L3243:
5228                     ; 16 	for(i=0;i<8;i++)
5230  0036 0c01          	inc	(OFST+0,sp)
5233  0038 7b01          	ld	a,(OFST+0,sp)
5234  003a a108          	cp	a,#8
5235  003c 25d2          	jrult	L5143
5236  003e               L5243:
5237                     ; 25 		PD_ODR=~(0x01<<checkFlag);
5239  003e 5f            	clrw	x
5240  003f b602          	ld	a,_checkFlag+1
5241  0041 2a01          	jrpl	L21
5242  0043 53            	cplw	x
5243  0044               L21:
5244  0044 97            	ld	xl,a
5245  0045 a601          	ld	a,#1
5246  0047 5d            	tnzw	x
5247  0048 2704          	jreq	L41
5248  004a               L61:
5249  004a 48            	sll	a
5250  004b 5a            	decw	x
5251  004c 26fc          	jrne	L61
5252  004e               L41:
5253  004e 43            	cpl	a
5254  004f c7500f        	ld	_PD_ODR,a
5256  0052 20ea          	jra	L5243
5286                     ; 32 @far @interrupt void SPI(void)
5286                     ; 33 {
5288                     	switch	.text
5289  0054               f_SPI:
5293                     ; 36 	if((SPI_SR&0x01)!=0)
5295  0054 c65203        	ld	a,_SPI_SR
5296  0057 a501          	bcp	a,#1
5297  0059 2726          	jreq	L1443
5298                     ; 40 	 Data[dataIndex]=SPI_DR;
5300  005b b600          	ld	a,_dataIndex
5301  005d 5f            	clrw	x
5302  005e 97            	ld	xl,a
5303  005f c65204        	ld	a,_SPI_DR
5304  0062 e700          	ld	(_Data,x),a
5305                     ; 41 	 PB_ODR=Data[dataIndex++];
5307  0064 b600          	ld	a,_dataIndex
5308  0066 97            	ld	xl,a
5309  0067 3c00          	inc	_dataIndex
5310  0069 9f            	ld	a,xl
5311  006a 5f            	clrw	x
5312  006b 97            	ld	xl,a
5313  006c e600          	ld	a,(_Data,x)
5314  006e c75005        	ld	_PB_ODR,a
5315                     ; 42 	 if(dataIndex==8)
5317  0071 b600          	ld	a,_dataIndex
5318  0073 a108          	cp	a,#8
5319  0075 260a          	jrne	L1443
5320                     ; 44 		 SPI_CR2|=10;
5322  0077 c65201        	ld	a,_SPI_CR2
5323  007a aa0a          	or	a,#10
5324  007c c75201        	ld	_SPI_CR2,a
5325                     ; 45 		dataIndex=0;
5327  007f 3f00          	clr	_dataIndex
5328  0081               L1443:
5329                     ; 49 	if((SPI_SR&0x10)!=0)
5331  0081 c65203        	ld	a,_SPI_SR
5332  0084 a510          	bcp	a,#16
5333  0086 2706          	jreq	L5443
5334  0088               L7443:
5335                     ; 53 		PD_ODR=0xaa;
5337  0088 35aa500f      	mov	_PD_ODR,#170
5339  008c 20fa          	jra	L7443
5340  008e               L5443:
5341                     ; 56 }
5344  008e 80            	iret
5386                     	xdef	f_SPI
5387                     	xdef	_main
5388                     	xdef	_checkFlag
5389                     	xdef	_dataIndex
5390                     	switch	.ubsct
5391  0000               _Data:
5392  0000 000000000000  	ds.b	8
5393                     	xdef	_Data
5394                     	xref	_IO_init
5395                     	xref	_SPI_SlaveInit
5396                     	xref.b	c_y
5416                     	end
