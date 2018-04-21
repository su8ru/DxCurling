#pragma once
#include <DxLib.h>
#include <math.h>
#include "define.h"

#define PI 3.141592653589793

void putStone(int id,double posx,double posy,bool yellow) {
	stones[id].x = posx;
	stones[id].y = posy;
	stones[id].vx = 0;
	stones[id].vy = 0;
	stones[id].isYellow = yellow;
}

void initStones() {
	putStone(0, 804, 36, true);
	putStone(1,516, 36, false);
	putStone(2,804, 100, true);
	putStone(3,516,100,false);
	putStone(4,804,164,true);
	putStone(5,516,164,false);
	putStone(6,804,228,true);
	putStone(7,516,228,false);
}



//常時

void DrawBrush() {
	DrawGraph(mX - 10, mY - 110, brush, TRUE);
}

void Error() {
	DrawBox(460, 320, 840, 400, 0xff0000, TRUE);
	DrawFormatStringToHandle(464, 328, 0xffffff, Cica32, "エラーが発生しました。\n部員を呼んでください。");
}


//OP,Pause,ED

void OP() {
	DrawFormatStringToHandle(544, 344, 0x000000, azukiLB32, "おーぷにんぐ");
	DrawFormatStringToHandle(440, 400, 0x000000, azukiLB24, "SPACEキーを押してスタート");
	if (key[KEY_INPUT_SPACE] == 1)	gamemode = 1;

}

void Pause() {
	DrawFormatStringToHandle(544, 344, 0x000000, azukiLB32, "ぽーずがめん");
	if (key[KEY_INPUT_SPACE] == 1)	gamemode = 1;
	if (key[KEY_INPUT_RETURN] == 1)	gamemode = 0;
}

void ED() {

}


void AddForce(int id, double x, double y) {
	stones[id].vx += x;
	stones[id].vx += y;
}

//Game


void Control() {
	if (!moveFlag) {
		if (key[KEY_INPUT_A])		angle--;
		else if (key[KEY_INPUT_D])	angle++;

		else if (key[KEY_INPUT_S] == 1) power--;
		else if (key[KEY_INPUT_W] == 1) power++;
	}

	if(angle<-30)angle=-30;
    if(angle>30)angle=30;
    if(power>5)power=5;
    if(power<1)power=1;

    if (key[KEY_INPUT_ESCAPE] == 1)	gamemode = 2;

	if (waitingForInput && key[KEY_INPUT_Q] == 1) {
		stones[gamecnt].x = 660;
		stones[gamecnt].y = 100;
		placed = true;
		waitingForInput = true;
	}
	if (waitingForInput && key[KEY_INPUT_E] == 1 && placed) {
		moveFlag = true;
		placed = false;
        stones[gamecnt].vx = power*sin(Rad(angle));
        stones[gamecnt].vy = power*cos(Rad(angle));
		waitingForInput = false;
	}
    if (!waitingForInput && !isMovingAnyStones()){
        gamecnt++;
		waitingForInput = true;
    }
    PhysicStone();
	StopSlowStone();
	StopOverStone();
}


void DrawStone() {
	for (int i = 0; i < 8; i++) {
		if (stones[i].isYellow)	DrawGraph((int)stones[i].x - 31, (int)stones[i].y - 32, stone_yellow, TRUE);
		else					DrawGraph((int)stones[i].x - 31, (int)stones[i].y - 32, stone_red,    TRUE);
	}
}


void DrawGame() {
	DrawGraph(481, 0, sheet, FALSE);
    DrawShootLineRad();
    //MoveStoneD();
    DrawStone();
    //MoveOverStone();

}



void StopSlowStone() {
	for (int i = 0; i < 8; i++) {
		if (stones[i].vx < 0.1 && stones[i].vy < 0.1) {
			moveFlag = false;
			nowStonePos = 0;
			stones[i].vx = 0;
			stones[i].vy = 0;
			turnEndFlag = true;
		}
	}
}

void StopOverStone() {
	for (int i = 0; i < 8; i++) {
		if (stones[i].y > 740) {
			stones[i].x = 10000;//はみ出たらもう消えろ
			stones[i].y = 10000;
			placed = false;
			moveFlag = false;
			nowStonePos = 0;
			turnEndFlag = true;
		}
	}
}

void PhysicStone() {
    for(int i=0;i<8;i++){
        stones[i].x+=stones[i].vx;
        stones[i].y+=stones[i].vy;
        stones[i].vx *= 0.995;
        stones[i].vy *= 0.995;
    }

    // TODO:衝突の処理はココらへん
}

bool isMovingAnyStones() {
	for (int i = 0;i < 8;i++) {
		if (stones[i].vx != 0 && stones[i].vy != 0) {
			return true;
		}
	}
	return false;
}


//Debug

void DrawInfo() {
	DrawFormatStringToHandle(0, 20, 0x000000, Cica16, "course:%d°,power:%d\nspeed:%f,nowStonePos:%f\nplaced:%s,moveFlag:%s", angle, power, speed, nowStonePos, placed?"true":"false", moveFlag?"true":"false");
}

void DrawMousePos() {
	DrawFormatStringToHandle(0, 0, 0x000000, Cica16, "X: %d Y: %d", mX, mY);
}

void DrawShootLine() {
	DrawLineAA((float)660, (float)100, (float)sX, (float)sY, 0x000000, (float)4);
}

void DrawShootLineRad() {
	DrawLineAA((float)660, (float)100, (float)660 + (float)sin(Rad(angle)) * (float)power*100, (float)100 + (float)cos(Rad(angle)) * (float)power*100, 0xff0000, 4);
}


double Rad(int deg) {
	return (double)deg * PI / 180;
}
