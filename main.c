//Name: Yaxiong Liu

//include libraries and pictures
#include "text.h"
#include "title.h"
#include "piece.h"
#include <stdio.h>
#include "cirno1.h"
#include "cirno2.h"
#include "reimu1.h"
#include "reimu2.h"
#include "alice.h"
#include "aya.h"
#include "marisa.h"
#include "patchouli.h"
#include "remi.h"
#include "sakuya.h"
#include "startscreen.h"
#include "gameclear.h"
#include "gameover.h"

//global variable initialization
int c,i,j,k,ir,jc,uci,ucj,ui,uj,idelay,counter,land,overState,score, difficulty,clearState,skillPoint,result,state;
canvas mycanvas; //the current canvas	
canvas oldcanvas; //hold the old canvas, use to refresh current canvas
tetro curr; //the current piece which is falling
tetro temp; //a temporary piece, use to rotate
tetro next; //hold the next piece

//function prototypes
void reset();
int chChoose();
char scoreStr[15];
int collicion(int* newr, int* newc);
int dcolli(canvas can);
int lcolli(canvas can);
int rcolli(canvas can);
void currIntoCanvas(canvas can, tetro te);
int checkgameover(canvas can, tetro te);
void sqsec();
int ucolli(canvas can, tetro curr);
int rowEli();
void difficultyIncrease();
void reimuSkill();
void cirnoSkill();

int main(void)
{
	REG_DISPCTL = MODE3 | BG2_ENABLE; //mode 3 and to enable background 2
	generatePieces(); //Initialize all types of pieces

	//allocate address for mycanvas, oldcanvas, curr, temp, next
	mycanvas=malloc(sizeof(*mycanvas)); 
	oldcanvas=malloc(sizeof(*oldcanvas));
	curr=malloc(sizeof(*curr));
	temp=malloc(sizeof(*temp));
	next=malloc(sizeof(*next));
	reset(); //start the game
	while(1) { //the while loop of the whole game process
		while(overState==0 && clearState==0) { //while the game is not over, neither clear, game continue
			copyOf(curr, next); //copy the next piece to current
			randomT(next);	//randomly generate the next piece
			fillColor(20,180,32,32,BLACK); //clear the next piece diaplay field
			draw(20,180,next); //draw the next piece
			currIntoCanvas(mycanvas,curr); //drop the current piece into canvas
			land=0; //the piece has not landed yet, also use to control jump out the following while loop
			while((land==0)&&(overState==0)&&(clearState==0)){ //while the piece is falling
				if(checkgameover(mycanvas,curr)){ //check if this piece will make game over
					overState = 1;
					break;
				}
				else if(dcolli(mycanvas)!=1){ //if the piece will not make collision downward, keep falling
					copyOfCan(oldcanvas, mycanvas);
					for(i=0;i<4;i++) {
						mycanvas->cr[i]++;
					}
					mycanvas->centerRow++;
					waitForVblank();
					clearPiece(oldcanvas,curr);
					drawPiece(mycanvas,curr);
				} else {// if the current piece landed, load the current piece into canvas, and jump out the loop for next peice
					drawPiece(mycanvas,curr);
					for(i=0;i<4;i++) mycanvas->code[mycanvas->cr[i]][mycanvas->cc[i]]=curr->color;
					break;
				}
				for(idelay=0;idelay<(7-difficulty);idelay++){// for loop is used to control the falling speed, namely the difficulty
					if(KEY_DOWN_NOW(KEY_R)){ //if press R, use the skill of character
						if(skillPoint==60){
							if(c==0) reimuSkill();
							else cirnoSkill();
							skillPoint=0;
							drawRect(86,11,60,3,BLACK);
							drawRect(75,20,51,10,BLACK);
						}

					}
					if(KEY_DOWN_NOW(KEY_DOWN)){ //if press down, jump out the loop for speed up falling
						for(i=0;i<1;i++) sqsec();
						break;
					}	
					if(KEY_DOWN_NOW(KEY_SELECT)){ //if press select, restart the game
						reset();
						land=1;
						break;
					}

					if(KEY_DOWN_NOW(KEY_LEFT)) {//if press left and the left moving will not make collision, then move to left
						if(lcolli(mycanvas)!=1){
							copyOfCan(oldcanvas, mycanvas);
							for(i=0;i<4;i++) {
								mycanvas->cc[i]--;
							}
							mycanvas->centerCol--;
							waitForVblank();
							clearPiece(oldcanvas,curr);
							drawPiece(mycanvas,curr);
						}
					}
					else if(KEY_DOWN_NOW(KEY_UP)) {//if press up and the rotation will not make collision, then rotate
						if(ucolli(mycanvas,curr)!=1){
							copyOfCan(oldcanvas, mycanvas);
							rotate(temp, curr);
							copyOf(curr,temp);
							counter = 0;
							for(ui=0;ui<4;ui++){
								for(uj=0;uj<4;uj++){
									if(curr->code[ui][uj]){
										mycanvas->cr[counter]=mycanvas->centerRow-1+ui;
										mycanvas->cc[counter]=mycanvas->centerCol-2+uj;
										counter++;
									}
								}
							}
							waitForVblank();
							clearPiece(oldcanvas,curr);
							drawPiece(mycanvas,curr);
						
						}
					}
					else if(KEY_DOWN_NOW(KEY_RIGHT)) {//if press right and the right moving will not make collision, then move to right
						if(rcolli(mycanvas)!=1){
							copyOfCan(oldcanvas, mycanvas);
							for(i=0;i<4;i++) {
								mycanvas->cc[i]++;
							}
							mycanvas->centerCol++;
							waitForVblank();
							clearPiece(oldcanvas,curr);
							drawPiece(mycanvas,curr);
						}
					}
					sqsec();
				}	
			}
			score=score+rowEli(mycanvas)*difficulty; //eliminate row while a row is full, and increase the score respectively
			drawRect(15, 5, 30, 10, BLACK); // display the score
			sprintf(scoreStr, "%d", score);
			text(15, 5, scoreStr, WHITE);
			if(score>(50*difficulty*difficulty)) difficultyIncrease(); //when the score reaches 50,200,450,800,1250,1800 increase the difficulty
			if(score>(50*7*7)) clearState=1; //if the score is higher 2450, then game clear
		}
		if(overState!=0) //if game over, show the game over picture
		{
			drawImage3(0, 0, 240, 160, gameover);
			while(1){
				if(KEY_DOWN_NOW(KEY_SELECT)){
					reset();
					break;
				}
			}
		} 
		else if(clearState!=0) //if game clear, show the game clear picture
		{
			drawImage3(0, 0, 240, 160, gameclear);
			while(1)
			{
				if(KEY_DOWN_NOW(KEY_SELECT))
				{
					reset();
					break;
				}
			}
		}
	}
	while(1);
	return 0;
}

void reset(){ //reset the game to the start
	drawImage3(0, 0, 240, 160, title); //draw the title screen
	difficulty=1; //restore the difficulty to 1
	int loop=1; //enable loop;
	volatile int y=0; //use to flash the word Press Start
	while(loop) {
		text(126,89,"Press Start", WHITE);
		if(loop){
			for(int i = 0; i<70000; i++) 
			{
				y++;
				if(KEY_DOWN_NOW(KEY_START)){
					loop=0;
					break;
				}
			}
		}
		y=0;
		drawRect(123,87,69,12,BLACK);
		if(loop){
			for(int i = 0; i<70000; i++) 
			{
				y++;
				if(KEY_DOWN_NOW(KEY_START)){
					loop=0;
					break;
				}
			}
		}
	}
	fillColor(0,0,240,160,BLACK); //if the palyer press start, clear the screen, and show the start screen
	drawImage3(0, 0, 240, 160, startscreen);
	while(1){ //player has to press A to make the start picture pass 
		if(KEY_DOWN_NOW(KEY_A)){			
			break;
		}
	}
	while(KEY_DOWN_NOW(KEY_A)); //if the player press A, show the start text
	drawRect(40,30,120,53,BLACK);
	text(45,40,"STRANGE PHENOMENA", WHITE);
	text(55,50,"HAPPENS AGAIN", WHITE);
	text(65,56,"IN GENSOKYO", WHITE);
	text(80,54,"TIME TO WORK", WHITE);
		while(1){
		if(KEY_DOWN_NOW(KEY_A)){			
			break;
		}
	}
	while(KEY_DOWN_NOW(KEY_A)); //if player press A, go to character choosing
	fillColor(0,0,240,160,BLACK);
	c=chChoose(); //who and save the character that player chose
	drawHollowRect(9,79,82,146,WHITE);
	if(c==0){
		drawImage3(95,20,38,40,reimu1);
		text(140,20,"Reimu",WHITE);
		text(150,20,"Hakurei",WHITE);
	}
	else{
		drawImage3(95,20,37,40,cirno1);
		text(140,20,"Cirno",WHITE);
		text(150,20,"9",WHITE);
	}
	text(5,180,"NEXT",WHITE); //initial the gaming field
	drawImage3(95,190,22,40,alice);
	text(140,175,"Alice",WHITE);
	text(150,175,"Margatroid",WHITE);
	score=0;
	text(5, 5, "Score", WHITE);
	sprintf(scoreStr, "%d", score);
	text(15, 5, scoreStr, WHITE);
	drawHollowRect(85,10,62,5,WHITE);	
	clearCanvas(mycanvas);
	copyOf(curr, next);
	randomT(next);
	fillColor(20,180,32,32,BLACK);
	draw(20,180,next);
	currIntoCanvas(mycanvas,curr);
	land=0;
	clearState=0;
	overState=0;
}

int chChoose() { //player chooses character
	int character=0;
	int cursorPosition=0;
	text(5,5,"Choose your character", WHITE);
	drawImage3(40,20,38,40,reimu1);
	text(41,63,"Character Name:",WHITE);
	text(51,70,"Reimu",WHITE);
	text(61,63,"Skill:",WHITE);
	text(71,70,"Fantasy Seal",WHITE);
	drawImage3(90,20,37,40,cirno1);
	text(91,63,"Character Name:",WHITE);
	text(101,70,"Cirno",WHITE);
	text(111,63,"Skill:",WHITE);
	text(121,70,"I'am the strongest",WHITE);
	cursor(56,10,WHITE);
	int loop=1;
	while(loop) // control the cursor
	{
		if(cursorPosition==0){
			if(KEY_DOWN_NOW(KEY_DOWN)){
				fillColor(56,10,7,12,BLACK);
				cursor(106,10,WHITE);
				character=1;
				cursorPosition=1;
			}
			if(KEY_DOWN_NOW(KEY_A)) break;
		}
		if(cursorPosition==1){
			if(KEY_DOWN_NOW(KEY_UP)){
				fillColor(106,10,7,12,BLACK);
				cursor(56,10,WHITE);
				character=0;
				cursorPosition=0;
			}
			if(KEY_DOWN_NOW(KEY_A)) break;
		}
	}
	fillColor(0,0,240,160,BLACK);
	return character;
}

void currIntoCanvas(canvas can, tetro te){ // drop the current piece into canvas
	int i,j;
	counter=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(te->code[i][j]){
				can->cr[counter]=i;
				can->cc[counter]=j+3;
				counter++;
			}
		}
	}
	can->centerRow=0;
	can->centerCol=5;
}

void sqsec(){ //timer use to control speed
	REG_TM2CNT = 0;
	REG_TM3CNT = 0;
	REG_TM2D = -0x5000;
	REG_TM3D = 0;
	REG_TM2CNT = TM_FREQ_64 | TM_ON;
	REG_TM3CNT = TM_CASCADE | TM_ON;
	while(REG_TM3D<1){}
}


int dcolli(canvas can){ //check downward collision
	int result = 0;
	int i;
	for(i=0;i<4;i++){
		if(can->cr[i]<17){
			if(can->code[can->cr[i]+1][can->cc[i]]){
				result = 1;
			}
		} else {
			result=1;
		}
	}
	return result;
}

int lcolli(canvas can){ //check left moving collision
	int result = 0;
	int i;
	for(i=0;i<4;i++){
		if(can->cc[i]>0){
			if(can->code[can->cr[i]][can->cc[i]-1]){
				result = 1;
			}
		} else {
			result=1;
		}
	}
	return result;
}

int rcolli(canvas can){ //check right moving collision
	int result = 0;
	int i;
	for(i=0;i<4;i++){
		if(can->cc[i]<9){
			if(can->code[can->cr[i]][can->cc[i]+1]){
				result = 1;
			}
		}
		else result=1;
	}
	return result;
}

int ucolli(canvas can, tetro curr){ //cheack rotation collision
	int result = 0;
	ir = can->centerRow-1;
	jc = can->centerCol-2;
	rotate(temp, curr);
	drawRect(30,5,32,32,BLACK);
	for(uci=0;uci<4;uci++){
		for(ucj=0;ucj<4;ucj++){
			if(temp->code[uci][ucj]){
				if(can->code[ir+uci][jc+ucj]) result = 1;
				else if(ir+uci<0) result=1;
				else if(ir+uci>17) result=1;
				else if(jc+ucj<0) result=1;
				else if(jc+ucj>9) result=1;
			}
		}
	}
	return result;
}



int checkgameover(canvas can, tetro te){ //check if the current piece will make game over
	int i,j;
	int result=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(te->code[i][j]){
				if(can->code[i][j+3]){
					result = 1;
					break;
				}
			}
		}
	}
	return result;
}

void difficultyIncrease(){ //increase the difficilty and change the opposite character
	difficulty++;
	fillColor(95,175,65,65,BLACK);
	if(difficulty==2) {
		drawImage3(95,190,23,40,aya);
		text(140,175,"Aya",WHITE);
		text(150,175,"Shameimaru",WHITE);
	} else if(difficulty==3) {
		drawImage3(95,190,32,40,patchouli);
		text(140,175,"Patchouli",WHITE);
		text(150,175,"Knowledge",WHITE);
	} else if(difficulty==4) {
		drawImage3(95,190,24,40,sakuya);
		text(140,175,"Sakuya",WHITE);
		text(150,175,"Izayoi",WHITE);
	} else if(difficulty==5) {
		drawImage3(95,190,36,40,remi);
		text(140,175,"Remilia",WHITE);
		text(150,175,"Scarlet",WHITE);
	} else if(difficulty==6) {
		drawImage3(95,190,33,40,marisa);
		text(140,175,"Marisa",WHITE);
		text(150,175,"Kirisame",WHITE);
	}
}

int rowEli() { //check if row can be eliminated, if yes, then do it, character will cheer up if at least one row has been eliminated
	int result = 0;
	int rows[4]={-1,-1,-1,-1};
	for(i=0;i<4;i++){
		state=1;
		for(j=0;j<10;j++){
			if(mycanvas->code[mycanvas->centerRow-1+i][j]==0) {
				state=0;
			}
		}
		if(state==1) {
			rows[result]=mycanvas->centerRow-1+i;
			result++;
		}
	}
	if(result>0){
		for(i=0;i<result;i++){
			for(k=rows[i];k>0;k--){
				for(j=0;j<10;j++){
					if(mycanvas->code[k-1][j]) mycanvas->code[k][j]=mycanvas->code[k-1][j];
					else mycanvas->code[k][j]=0;
				}
			}
		}
		for(i=0;i<10;i++) mycanvas->code[0][i]=0;
		drawCanvas(mycanvas);
	}
	if(result>0){ //if at least one row has been eliminated, cheer
		if(c==0){
			for(i=0;i<3;i++){
				drawImage3(95,20,38,40,reimu2);			
				for(j=0;j<2;j++) sqsec();
				drawImage3(95,20,38,40,reimu1);
				for(j=0;j<2;j++) sqsec();
			}
		} else {
			for(i=0;i<3;i++){
				drawImage3(95,20,37,40,cirno2);			
				for(j=0;j<2;j++) sqsec();
				drawImage3(95,20,37,40,cirno1);
				for(j=0;j<2;j++) sqsec();
			}
		}
		skillPoint=skillPoint+3*result;
		if(skillPoint>60) skillPoint=60;
		if(skillPoint==60) text(75,20,"READY!",WHITE);
		drawRect(86,11,skillPoint,3,CYAN);
	}
	return result;
}

void reimuSkill(){ //the skill of character reimu, eliminate the bottom 3 rows
	copyOfCan(oldcanvas,mycanvas);
	int reimuRows[3]={17,16,15};

	for(i=0;i<3;i++){
		for(k=reimuRows[i];k>0;k--){
			for(j=0;j<10;j++){
				if(mycanvas->code[k-1][j]) mycanvas->code[k][j]=mycanvas->code[k-1][j];
				else mycanvas->code[k][j]=0;
			}
		}
	}
	for(i=0;i<10;i++) mycanvas->code[0][i]=0;
	waitForVblank();
	clearPiece(oldcanvas,curr);
	drawCanvas(mycanvas);
	drawPiece(mycanvas, curr);
}

void cirnoSkill(){ //the skill of character reimu, eliminate left and right side triangle shape
	copyOfCan(oldcanvas,mycanvas);
	for(j=0;j<5;j++){
		for(i=8+j;i<18-j;i++) {
			mycanvas->code[i][j]=0;
			mycanvas->code[i][9-j]=0;
		}
	}
	waitForVblank();
	clearPiece(oldcanvas,curr);
	drawCanvas(mycanvas);
	drawPiece(mycanvas, curr);
}





















