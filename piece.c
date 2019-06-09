//Name:Yaxiong Liu

#include "piece.h"

void draw(int r, int c, tetro p) { //draw a piece at given position
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(p->code[i][j]) fillColor(r+8*i,c+8*j,8,8,p->color);
		}
	}

}

void drawCanvas(canvas can){ //draw the canvas, not includin the current piece
	int i,j;
	for(i=0;i<18;i++){
		for(j=0;j<10;j++){
			fillColor(10+i*8, 80+8*j, 8, 8, can->code[i][j]);
		}
	}
}

void drawPiece(canvas can, tetro p) { //draw the current piece in the current canvas
	int i;
	for(i=0;i<4;i++){
		fillColor(10+can->cr[i]*8,80+can->cc[i]*8,8,8,p->color);
	}
}

void clearPiece(canvas can, tetro p) { //clear the current piece in the current canvas
	int i;
	for(i=0;i<4;i++){
		fillColor(10+can->cr[i]*8,80+can->cc[i]*8,8,8,BLACK);
	}
}
void clearCanvas(canvas can){ //clear a canvas
	int i,j;
	for(i=0;i<18;i++){
		for(j=0;j<10;j++){
			can->code[i][j]=0;
		}
	}
	for(i=0;i<4;i++){
		can->cr[i]=0;
		can->cc[i]=0;
	}
	can->centerRow=0;
	can->centerCol=0;
}

void copyOf(tetro new, tetro old) { //copy a piece
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(old->code[i][j]) {
				new->code[i][j]=1;
			}
			else new->code[i][j]=0;
		}
	}
	new->color=old->color;
	new->name=old->name;
	new->state=old->state;
}

void copyOfCan(canvas new, canvas old) { //copy canvas
	int i,j;
	for(i=0;i<18;i++){
		for(j=0;j<10;j++){
			if(old->code[i][j]) new->code[i][j]=old->code[i][j];
			else new->code[i][j]=0;
		}
	}
	for(i=0;i<4;i++){
		new->cr[i]=old->cr[i]; 
		new->cc[i]=old->cc[i]; 
	}
	new->centerRow=old->centerRow;
	new->centerCol=old->centerCol;
}

void rotate(tetro new, tetro old) { //rotate a piece

	if(old->name==0) {
		copyOf(new,old);
	}
	else if((old->name==1) && (old->state==1)){
		copyOf(new, it);
	}
	else{
		int rotatei,rotatej;
		for(rotatei=0;rotatei<4;rotatei++){
			for(rotatej=0;rotatej<4;rotatej++){
				if(old->code[rotatei][rotatej]) new->code[3-rotatej][rotatei+1]=old->code[rotatei][rotatej];
				else new->code[3-rotatej][rotatei+1]=0;
			}
		}
		new->color=old->color;
		new->name=old->name;
		if((old->name==4) || (old->name==5) || (old->name==6)){
			if(old->state!=3) new->state=old->state+1;
			else new->state=0;
		} else {
			if(old->state!=1) new->state=1;
			else new->state=0;
		}
	}
}

void randomT(tetro te) { //randomly generate a piece
	int num = rand()%7;
	if(num==0) copyOf(te, ot);
	else if(num==1) copyOf(te, it);
	else if(num==2) copyOf(te, st);
	else if(num==3) copyOf(te, zt);
	else if(num==4) copyOf(te, lt);
	else if(num==5) copyOf(te, jt);
	else copyOf(te, tt);
}

void generatePieces() { //initialize all types of pieces
	u16 temp;
	int i,j;

	ot=malloc(sizeof(*ot));
	temp = 0x0660;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(((temp)&(1))==1) ot->code[3-i][3-j]=1;
			temp=(temp>>1);
		}
	}
	ot->color=YELLOW;
	ot->name=0;
	ot->state=0;

	it=malloc(sizeof(*it));
	temp = 0x0F00;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(((temp)&(1))==1) it->code[3-i][3-j]=1;
			temp=(temp>>1);
		}
	}
	it->color=RED;
	it->name=1;
	it->state=0;
	
	jt=malloc(sizeof(*jt));
	temp = 0x0710;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(((temp)&(1))==1) jt->code[3-i][3-j]=1;
			temp=(temp>>1);
		}
	}
	jt->color=BLUE;
	jt->name=5;
	jt->state=0;

	lt=malloc(sizeof(*lt));
	temp = 0x0740;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(((temp)&(1))==1) lt->code[3-i][3-j]=1;
			temp=(temp>>1);
		}
	}
	lt->color=ORANGE;
	lt->name=4;
	lt->state=0;
	
	st=malloc(sizeof(*st));
	temp = 0x0360;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(((temp)&(1))==1) st->code[3-i][3-j]=1;
			temp=(temp>>1);
		}
	}
	st->color=MAGENTA;
	st->name=2;
	st->state=0;

	tt=malloc(sizeof(*tt));
	temp = 0x0720;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(((temp)&(1))==1) tt->code[3-i][3-j]=1;
			temp=(temp>>1);
		}
	}
	tt->color=CYAN;
	tt->name=6;
	tt->state=0;

	zt=malloc(sizeof(*zt));
	temp = 0x0630;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(((temp)&(1))==1) zt->code[3-i][3-j]=1;
			//else zt.code[3-i][3-j]=0;
			temp=(temp>>1);
		}
	}
	zt->color=LIME;
	zt->name=3;
	zt->state=0;
}
