//Name:Yaxiong Liu

#include "mylib.h"
#include "text.h"

//print char on screen start at pixel (r,c)
void chartext(int row, int col, char ch, u16 color)
{
	int r,c;
	for(r=0;r<8;r++)
	{
		for(c=0;c<6;c++)
		{
			if(fontdata_6x8[r*6+c+ch*48]==1) // for each pixel, if matches the font data, then set the pixel to give color
			{
				setPixel(row+r,col+c,color);
			}
		}
	}
}
//print each char of a string
void text(int row, int col, char *str, u16 color)
{
	while(*str)
	{
		chartext(row,col,*str++,color);
		col+=6;
	}
}
