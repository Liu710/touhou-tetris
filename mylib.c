//Name:Yaxiong Liu

#include "mylib.h"

u16 *videoBuffer = (u16 *)0x6000000; // initialize videoBuffer

//A function to set pixel (r,c) to the color passed in
void setPixel(int r, int c, u16 color)
{
  videoBuffer[OFFSET(r,c)] = color; //Set pixel (r,c) to the given color
} // end setPixel


//A function to draw a filled rectangle starting at (r,c)
void drawRect(int r, int c, int width, int height, u16 color)
{
  int i; //the current height
  int j; //the current width
  for(i = 0; i < height; i++)
  {
    for(j = 0; j < width; j++)
    {
      videoBuffer[OFFSET((r+i),(c+j))] = color; //set pixel ((r+i),(c+j)) to the give color
    }
  }	
}

//A function to draw a hollow ractangle starting at (r,c)
void drawHollowRect(int r, int c, int width, int height, u16 color)
{
  int i; //the current height
  int j; //the current width
  for(j = 0; j < width; j++)
  {
    videoBuffer[OFFSET(r,(c+j))] = color; //Set the upper bound of the rectangle
  }
  for(i = 1; i < (height - 1); i++)
  {
    videoBuffer[OFFSET((r+i),c)] = color; //Set the left bound at row r+i
    videoBuffer[OFFSET((r+i),(c+width-1))] = color; //Set the right bound r+i
  }
  for(j = 0; j < width; j++)
  {
    videoBuffer[OFFSET((r+height-1),(c+j))] = color; // Set the lower bound of the rectangle
  }
}

//draw a cursor start at pixel (row,col)
void cursor(int row, int col, u16 color)
{
	for (int i = 0; i<7; i++)
		setPixel((row+i), col, color);
	for (int i = 1; i<6; i++)
		setPixel((row+i), (col+1), color);
	for (int i = 2; i<5; i++)
		setPixel((row+i), (col+2), color);
	setPixel((row+3), (col+3), color);
}

//draw a picture start at pixel (row,col)
void drawImage3(int r, int c, int width, int height, const u16* image)
{
	for(int i = 0; i < height; i++) {
		DMA[3].cnt = 0;
		DMA[3].src = image + i*width;
	        DMA[3].dst = videoBuffer + OFFSET((r+i), c);
	        DMA[3].cnt = width | DMA_ON;
	}
}

//fill color at given position by using DMA
void fillColor(int r, int c, int width, int height, u16 color) {
	for(int i = 0; i < height; i++) {
		DMA[3].cnt = 0;
		DMA[3].src = &color;
	        DMA[3].dst = videoBuffer + OFFSET((r+i), c);
	        DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}
