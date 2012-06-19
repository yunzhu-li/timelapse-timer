#include <XSTC89.h>
#include <delayms.h>



sbit RS=P2^4;
sbit RW=P2^5;
sbit E=P2^6;


char data chr1;



void writecmd(unsigned char cmd)
{
	DelayMs(1);
	E=0;
	RS=0;
	RW=0;
 	//_nop_();
	E=1;
	P0=cmd;
	E=0;
	RS=0;

}

void writedata(unsigned char dat)
{
	DelayMs(1);
	E=0;
	RS=1;
	RW=0;
	//_nop_();
	E=1;
	P0=dat;
	E=0;
	RS=0;

}

void showchar(unsigned char pos,unsigned char chr)
{
	unsigned char p;
	if (pos>=0x10)
	p=pos+0xb0; //是第二行则命令代码高4位为
	else 
	p=pos+0x80; //是第二行则命令代码高4位为
	
	writecmd (p);//写命令
	writedata (chr);   //写数据

}

void lcdshowstring(unsigned char line,char *ptr)
{

	unsigned char pos;
	int i;
	
	//pos+=(line*0x10);
	pos=0x10*line;


	for (i=0;i<16;i++)

		showchar(pos++,*(ptr+i));

}

void lcdinit()
{
	DelayMs(10);
	writecmd(0x38); //display mode
	writecmd(0x38); //display mode
	writecmd(0x38); //display mode
	writecmd(0x06); //显示光标移动位置
	writecmd(0x0c); //显示开及光标设置
	writecmd(0x01); //显示清屏

}

/*
void main()
{
	int j,k;
	j=32;k=0x10;

	lcdinit();
	
	sprintf(str1,"-FAT LYZ-       ");
	lcdshowstring(0,str1);
	sprintf(str1,"LCD1602 LCD1602 ");
	lcdshowstring(1,str1);

	
	while(j<256)
		{
			
			showchar(k++,j);
			P1=j++;
			if (k==0x20) k=0x10;
			DelayMs(30);
			
		}
		
	while(1);
		
	
}
*/
