#ifndef __LCD1602__
#define __LCD1602__

#include<stdio.h>

void lcdinit();
void showchar(unsigned char pos,unsigned char chr);
void lcdshowstring(unsigned char line,char *ptr);



#endif