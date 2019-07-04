   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.8 - 03 Dec 2008
2786                     	bsct
2787  0000               _table:
2788  0000 c0            	dc.b	192
2789  0001 f9            	dc.b	249
2790  0002 a4            	dc.b	164
2791  0003 b0            	dc.b	176
2792  0004 99            	dc.b	153
2793  0005 92            	dc.b	146
2794  0006 82            	dc.b	130
2795  0007 f8            	dc.b	248
2796  0008 80            	dc.b	128
2797  0009 90            	dc.b	144
2798  000a 88            	dc.b	136
2799  000b 83            	dc.b	131
2800  000c c6            	dc.b	198
2801  000d a1            	dc.b	161
2802  000e 86            	dc.b	134
2803  000f 8e            	dc.b	142
2854                     ; 17 void delay(uint s)
2854                     ; 18 {
2856                     	switch	.text
2857  0000               _delay:
2859  0000 89            	pushw	x
2860  0001 88            	push	a
2861       00000001      OFST:	set	1
2864                     ; 20  for(s;s>0;s--)
2867  0002 2011          	jra	L7102
2868  0004               L3102:
2869                     ; 21    for(i=0;i<100;i++);
2871  0004 0f01          	clr	(OFST+0,sp)
2872  0006               L3202:
2876  0006 0c01          	inc	(OFST+0,sp)
2879  0008 7b01          	ld	a,(OFST+0,sp)
2880  000a a164          	cp	a,#100
2881  000c 25f8          	jrult	L3202
2882                     ; 20  for(s;s>0;s--)
2884  000e 1e02          	ldw	x,(OFST+1,sp)
2885  0010 1d0001        	subw	x,#1
2886  0013 1f02          	ldw	(OFST+1,sp),x
2887  0015               L7102:
2890  0015 1e02          	ldw	x,(OFST+1,sp)
2891  0017 26eb          	jrne	L3102
2892                     ; 22 }
2895  0019 5b03          	addw	sp,#3
2896  001b 81            	ret
2931                     ; 24 void init_IO(void)
2931                     ; 25 {
2932                     	switch	.text
2933  001c               _init_IO:
2937                     ; 26     PB_DDR=0XFF;
2939  001c 35ff5007      	mov	_PB_DDR,#255
2940                     ; 27     PB_CR1=0XFF;
2942  0020 35ff5008      	mov	_PB_CR1,#255
2943                     ; 28     PB_CR2=0X00;
2945  0024 725f5009      	clr	_PB_CR2
2946                     ; 30     PC_DDR=0X8f;           //MISO从设备输出管脚，MOSI从设备 输入
2948  0028 358f500c      	mov	_PC_DDR,#143
2949                     ; 31     PC_CR1=0X0f;
2951  002c 350f500d      	mov	_PC_CR1,#15
2952                     ; 32     PC_CR2=0X00;
2954  0030 725f500e      	clr	_PC_CR2
2955                     ; 34 		PD_DDR=0x48;
2957  0034 35485011      	mov	_PD_DDR,#72
2958                     ; 35 		PD_CR1=0x28;
2960  0038 35285012      	mov	_PD_CR1,#40
2961                     ; 36 		PD_CR2=0x00; 
2963  003c 725f5013      	clr	_PD_CR2
2964                     ; 38     PE_DDR=0x00;      //将SPI_NSS配置为上拉输入
2966  0040 725f5016      	clr	_PE_DDR
2967                     ; 39 		PE_CR1=0x20;
2969  0044 35205017      	mov	_PE_CR1,#32
2970                     ; 40 		PE_CR2=0x00;
2972  0048 725f5018      	clr	_PE_CR2
2973                     ; 41 }
2976  004c 81            	ret
3006                     ; 43 void init_TIM2(void)
3006                     ; 44 {
3007                     	switch	.text
3008  004d               _init_TIM2:
3012                     ; 45     TIM2_EGR=0X01;       //允许产生更新事件
3014  004d 35015304      	mov	_TIM2_EGR,#1
3015                     ; 46     TIM2_PSCR=0X00;     //不分频，使频率为2MHz
3017  0051 725f530c      	clr	_TIM2_PSCR
3018                     ; 48     TIM2_ARRH=0X27;     //更新后计数器的值
3020  0055 3527530d      	mov	_TIM2_ARRH,#39
3021                     ; 49     TIM2_ARRL=0X10;
3023  0059 3510530e      	mov	_TIM2_ARRL,#16
3024                     ; 51     TIM2_CR1=0X05;      //允许定时器工作
3026  005d 35055300      	mov	_TIM2_CR1,#5
3027                     ; 52     TIM2_IER=0X01;     //允许更新中断
3029  0061 35015301      	mov	_TIM2_IER,#1
3030                     ; 53         _asm("rim");       //汇编语句，启动定时器	
3033  0065 9a            rim
3035                     ; 54 }
3038  0066 81            	ret
3070                     ; 57 void SPI(void)
3070                     ; 58 { 
3071                     	switch	.text
3072  0067               _SPI:
3076                     ; 59 	SPI_CR1=0x10;                   //先发送MSB，关闭SPI，波特率为f/4，配置为从设备，空闲低电平，第一个时钟边缘开始数据采样
3078  0067 35105200      	mov	_SPI_CR1,#16
3079                     ; 60 	SPI_CR1|=0x40;                  //开启SPI
3081  006b 721c5200      	bset	_SPI_CR1,#6
3082                     ; 61 	SPI_CR2=0x00;
3084  006f 725f5201      	clr	_SPI_CR2
3085                     ; 62 	PD_DDR=0x48;
3087  0073 35485011      	mov	_PD_DDR,#72
3088                     ; 63   PD_CR1=0x28;
3090  0077 35285012      	mov	_PD_CR1,#40
3091                     ; 64 	delay(1000);
3093  007b ae03e8        	ldw	x,#1000
3094  007e ad80          	call	_delay
3096                     ; 65 	if((SPI_SR&0x01)==0x01)	//判断接收区是否为空，即判断是否接收到数据
3098  0080 c65203        	ld	a,_SPI_SR
3099  0083 a401          	and	a,#1
3100  0085 a101          	cp	a,#1
3101  0087 261b          	jrne	L1602
3102                     ; 67 		{delay(1);
3104  0089 ae0001        	ldw	x,#1
3105  008c cd0000        	call	_delay
3107                     ; 68 	   a=SPI_DR;
3109  008f 5552040005    	mov	_a,_SPI_DR
3110                     ; 69 		 PD_DDR|=a;
3112  0094 c65011        	ld	a,_PD_DDR
3113  0097 ba05          	or	a,_a
3114  0099 c75011        	ld	_PD_DDR,a
3115                     ; 70 		PD_CR1|=a;
3117  009c c65012        	ld	a,_PD_CR1
3118  009f ba05          	or	a,_a
3119  00a1 c75012        	ld	_PD_CR1,a
3120  00a4               L1602:
3121                     ; 72 	delay(1000);
3123  00a4 ae03e8        	ldw	x,#1000
3124  00a7 cd0000        	call	_delay
3127  00aa               L5602:
3128                     ; 74 	while((SPI_SR|0x80)==0x80);    //等待通信结束
3130  00aa c65203        	ld	a,_SPI_SR
3131  00ad aa80          	or	a,#128
3132  00af a180          	cp	a,#128
3133  00b1 27f7          	jreq	L5602
3134                     ; 75 	b=0x55;  	//将接受到的数取反后发送给主设备
3136  00b3 35550004      	mov	_b,#85
3137                     ; 78 	SPI_DR=b;                     //将要发送的b放到SPI_DR中
3139  00b7 35555204      	mov	_SPI_DR,#85
3140                     ; 79 	delay(1000);                      //延时一会，等待发送完毕
3142  00bb ae03e8        	ldw	x,#1000
3143  00be cd0000        	call	_delay
3146  00c1               L3702:
3147                     ; 80 	while((SPI_SR|0x80)==0x80);    //等待通信结束 
3149  00c1 c65203        	ld	a,_SPI_SR
3150  00c4 aa80          	or	a,#128
3151  00c6 a180          	cp	a,#128
3152  00c8 27f7          	jreq	L3702
3153                     ; 81 	delay(1);
3155  00ca ae0001        	ldw	x,#1
3156  00cd cd0000        	call	_delay
3158                     ; 82 }
3161  00d0 81            	ret
3191                     ; 84 void display(void)
3191                     ; 85 {
3192                     	switch	.text
3193  00d1               _display:
3197                     ; 86 	H=a/16;
3199  00d1 b605          	ld	a,_a
3200  00d3 4e            	swap	a
3201  00d4 a40f          	and	a,#15
3202  00d6 b701          	ld	_H,a
3203                     ; 87 	L=a%16; 
3205  00d8 b605          	ld	a,_a
3206  00da a40f          	and	a,#15
3207  00dc b700          	ld	_L,a
3208                     ; 88 	if((t%2)==0)
3210  00de b603          	ld	a,_t
3211  00e0 a501          	bcp	a,#1
3212  00e2 260d          	jrne	L7012
3213                     ; 90     PC_ODR=0x02;	
3215  00e4 3502500a      	mov	_PC_ODR,#2
3216                     ; 91     PB_ODR=table[H];	
3218  00e8 b601          	ld	a,_H
3219  00ea 5f            	clrw	x
3220  00eb 97            	ld	xl,a
3221  00ec e600          	ld	a,(_table,x)
3222  00ee c75005        	ld	_PB_ODR,a
3223  00f1               L7012:
3224                     ; 94 	if((t%2)!=0)
3226  00f1 b603          	ld	a,_t
3227  00f3 a501          	bcp	a,#1
3228  00f5 270d          	jreq	L1112
3229                     ; 96     PC_ODR=0x00;	
3231  00f7 725f500a      	clr	_PC_ODR
3232                     ; 97     PB_ODR=table[L];	
3234  00fb b600          	ld	a,_L
3235  00fd 5f            	clrw	x
3236  00fe 97            	ld	xl,a
3237  00ff e600          	ld	a,(_table,x)
3238  0101 c75005        	ld	_PB_ODR,a
3239  0104               L1112:
3240                     ; 99 }
3243  0104 81            	ret
3270                     ; 101 void main()
3270                     ; 102 {
3271                     	switch	.text
3272  0105               _main:
3276                     ; 103 	init_IO();
3278  0105 cd001c        	call	_init_IO
3280                     ; 104 	init_TIM2();
3282  0108 cd004d        	call	_init_TIM2
3284  010b               L3212:
3285                     ; 107     SPI();
3287  010b cd0067        	call	_SPI
3289                     ; 108 		display();
3291  010e adc1          	call	_display
3294  0110 20f9          	jra	L3212
3319                     ; 112 @far @interrupt void TIM2_UP_IRQHandler (void)         
3319                     ; 113 
3319                     ; 114 {
3321                     	switch	.text
3322  0112               f_TIM2_UP_IRQHandler:
3326                     ; 115    TIM2_SR1 = 0x00; 
3328  0112 725f5302      	clr	_TIM2_SR1
3329                     ; 116      t++;
3331  0116 3c03          	inc	_t
3332                     ; 117 }
3335  0118 80            	iret
3453                     	xdef	f_TIM2_UP_IRQHandler
3454                     	xdef	_main
3455                     	xdef	_display
3456                     	xdef	_SPI
3457                     	xdef	_init_TIM2
3458                     	xdef	_init_IO
3459                     	xdef	_delay
3460                     	switch	.ubsct
3461  0000               _L:
3462  0000 00            	ds.b	1
3463                     	xdef	_L
3464  0001               _H:
3465  0001 00            	ds.b	1
3466                     	xdef	_H
3467  0002               _n:
3468  0002 00            	ds.b	1
3469                     	xdef	_n
3470  0003               _t:
3471  0003 00            	ds.b	1
3472                     	xdef	_t
3473  0004               _b:
3474  0004 00            	ds.b	1
3475                     	xdef	_b
3476  0005               _a:
3477  0005 00            	ds.b	1
3478                     	xdef	_a
3479                     	xdef	_table
3499                     	end
