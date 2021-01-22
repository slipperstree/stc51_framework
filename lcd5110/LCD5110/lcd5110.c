

#include "bsp/bsp.h"

#include "lcd5110/lcd5110.h"


void LCD5110_TxByte(u8 byte,u8 dat)
{
	u8 i;

	if(dat)
		LCD5110_SET_RS;
	else
		LCD5110_CLR_RS;
	LCD5110_CLR_CS;
	LCD5110_DLY;

	for(i=0;i<8;i++)
	{
		if(byte & 0x80)
			LCD5110_SET_DIO;
		else
			LCD5110_CLR_DIO;
		LCD5110_SET_SCK;
		LCD5110_DLY;
		LCD5110_CLR_SCK;
		LCD5110_DLY;
		byte = byte << 1;
	}
	LCD5110_DLY;

	LCD5110_SET_CS;
}



void LCD5110_Init(void)
{
	u16 i;

	//��ʼ��port
	LCD5110_CLR_LED;
	LCD5110_SET_CS;
	LCD5110_CLR_RS;
	LCD5110_CLR_SCK;
	LCD5110_CLR_DIO;

    // ����һ����LCD��λ�ĵ͵�ƽ����
	LCD5110_CLR_RST;
	for(i=0;i<1000;i++);
	LCD5110_SET_RST;

	//����
	LCD5110_CLR_CS;
	for(i=0;i<100;i++);
	LCD5110_SET_CS;

    LCD5110_TxByte(0x21,0);	// ʹ����չ��������LCDģʽ
	// ����ƫ�õ�ѹ
	//LCD5110_TxByte(0xd0,0);	
    //LCD5110_TxByte(0xc8,0);
	LCD5110_TxByte(0xc0,0);
	
    LCD5110_TxByte(0x06,0);	// �¶�У��
    LCD5110_TxByte(0x13,0);	// 1:48
    LCD5110_TxByte(0x20,0);	// ʹ�û�������
    LCD5110_TxByte(0x0c,0);	// �趨��ʾģʽ��������ʾ




}

void LCD5110_Clear(u8 dat)
{
    u16 i;
    LCD5110_TxByte(0x0c,0);	
    LCD5110_TxByte(0x80,0);
    for (i=0; i<504; i++)
	{
        LCD5110_TxByte(dat,1);
	}
}

//����Y,48bit������X,84bit
//��λ����
u8 LCD5110_SetXY(u8 x, u8 y)
{
	if(x<=83 && y<=5)
	{
    	LCD5110_TxByte(0x40 | y,0);// row��
    	LCD5110_TxByte(0x80 | x,0);// column��
		return 1;
	}
	else
		return 0;
}


//��5,��8��Ӣ���ַ���dat�ĳ���Ϊ5
//x����ռ6�㣬y����ռ8��
void LCD5110_Disp5x8(u8 x, u8 y, u8* dat)
{
	u8 i;
	if(LCD5110_SetXY(x,y))
	{
		for(i=0;i<5;i++)
			LCD5110_TxByte(dat[i],1);	
	}
}

//��8,��16��Ӣ���ַ���dat�ĳ���Ϊ16
void LCD5110_Disp8x16(u8 x, u8 y, u8* dat)
{
	u8 i;
	if(LCD5110_SetXY(x,y))
	{
		for(i=0;i<8;i++)
			LCD5110_TxByte(dat[i],1);
	}
	if(LCD5110_SetXY(x,y+1))
	{
		for(i=8;i<16;i++)
			LCD5110_TxByte(dat[i],1);
	}	
}

//��12,��24��Ӣ���ַ���dat�ĳ���Ϊ36
void LCD5110_Disp12x24(u8 x, u8 y, u8* dat)
{
	u8 i;
	if(LCD5110_SetXY(x,y))
	{
		for(i=0;i<12;i++)
			LCD5110_TxByte(dat[i],1);
	}
	if(LCD5110_SetXY(x,y+1))
	{
		for(i=12;i<24;i++)
			LCD5110_TxByte(dat[i],1);
	}
	if(LCD5110_SetXY(x,y+2))
	{
		for(i=24;i<36;i++)
			LCD5110_TxByte(dat[i],1);
	}	
}
















