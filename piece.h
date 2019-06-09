//Name: Yaxiong Liu

#include <stdlib.h>
#include "mylib.h"

//structure of pieces
typedef struct {
	int code[4][4]; //the shape of a piece represented by a two dimensional array
	u16 color; // the color of a piece
	int name; // the code name of a piece
	int state; // the current rotation state 
} *tetro;
tetro ot;
tetro it;
tetro jt;
tetro lt;
tetro st;
tetro tt;
tetro zt;

//structure of canvas (game playing field)
typedef struct{
	u16 code[18][10]; //the canvas represented by a two dimensional array
	int cr[4]; //the row numbers of current falling piece
	int cc[4]; //the colomn numbers of current falling piece
	int centerRow; //the row numbers of the center of the current falling piece
	int centerCol; //the row numbers of the center of the current falling piece
} *canvas;

//function prototypes
void generatePieces();
void drawPiece(canvas can, tetro p);
void rotate(tetro, tetro);
void copyOf(tetro, tetro);
void randomT(tetro);
void clearPiece(canvas can, tetro p);
void timerSetUp();
void draw(int r, int c, tetro p); 
void drawCanvas(canvas);
void copyOfCan(canvas, canvas);
void clearCanvas(canvas can);

















