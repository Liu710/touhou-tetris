//Name: Yaxiong Liu

#define RGB(r,g,b) ((r)|((g)<<5)|((b)<<10)) //macro to setup color in RGB
#define REG_DISPCTL *(u16 *)0x4000000 //display control register
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define RED RGB(31,0,0) //RGB of red
#define ORANGE RGB(31,13,0) //RGB of grass green
#define BLUE RGB(0,0,31) //RGB of blue
#define YELLOW RGB(31,31,0) //RGB of sky blue
#define WHITE RGB(31,31,31) //RGB of white
#define MAGENTA RGB(31,0,31) //RGB of gray
#define CYAN RGB(0,31,31)
#define LIME RGB(23,31,0)  
#define BLACK 0 //RGB of black
#define OFFSET(row,col) ((row)*240+(col)) //OFFSET is used to locate pixel position by row and column
//Keys
#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_SELECT 0x0004
#define KEY_START 0x0008
#define KEY_RIGHT 0x0010
#define KEY_LEFT 0x0020
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080
#define KEY_R 0x0100
#define KEY_L 0x0200
#define BUTTONS *(u32 *)0x4000130 //the button state at memory 0x4000130
#define KEY_DOWN_NOW(key) (~(BUTTONS) & key) //If the key is not pressed, the macro return 0, or other values otherwise

typedef unsigned short u16; //alias of the unsigned short type
typedef unsigned int u32; //alias of the unsigned int type
typedef unsigned char u8; //alias of the unsigned char type
extern unsigned short *videoBuffer;
#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)
//DMA

/* DMA */

#define REG_DMA0SAD         *(const volatile u32*)0x40000B0 // source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(const volatile u32*)0x40000BC // source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(const volatile u32*)0x40000C8 // source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(const volatile u32*)0x40000D4 // source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register

typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	u32                  cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

//timer

#define REG_TM0CNT *(volatile u16*)0x4000102
#define REG_TM1CNT *(volatile u16*)0x4000106
#define REG_TM2CNT *(volatile u16*)0x400010A
#define REG_TM3CNT *(volatile u16*)0x400010E
#define REG_TM0D *(volatile u16*)0x4000100
#define REG_TM1D *(volatile u16*)0x4000104
#define REG_TM2D *(volatile u16*)0x4000108
#define REG_TM3D *(volatile u16*)0x400010C
#define TM_FREQ_1 0
#define TM_FREQ_64 1
#define TM_FREQ_256 2
#define TM_FREQ_1024 3
#define TM_CASCADE (1<<2)
#define TM_IRQ (1<<6)
#define TM_ON (1<<7)

//function prototype
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void cursor(int row, int col, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);
void waitForVblank();
void fillColor(int r, int c, int width, int height, u16 color);
