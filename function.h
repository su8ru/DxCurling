#pragma once
#include <DxLib.h>
#include <math.h>
#include "define.h"

#define PI 3.141592653589793


//常時

void DrawBrush() {
	DrawGraph(mX - 10, mY - 110, brush, TRUE);
}

void Draw() {
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE); //白背景
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


//Game


void Control() {
	if (!moveFlag) {
		if (key[KEY_INPUT_A] == 1)		course--;
		else if (key[KEY_INPUT_D] == 1)	course++;

		else if (key[KEY_INPUT_S] == 1) power--;
		else if (key[KEY_INPUT_W] == 1) power++;
	}

	switch (course) {
	case 7:
		course = 6;
		break;
	case -7:
		course = -6;
		break;
	}
	switch (power) {
	case 6:
		power = 5;
		break;
	case 0:
		power = 1;
		break;
	}
}

void DrawControl() {

}

void DrawStone() {
	for (int i = 0; i < 4; i++) {
		if (stoneInfo[i].isYellow)	DrawGraph((int)stoneInfo[i].x - 31, (int)stoneInfo[i].y - 32, stone_yellow, TRUE);
		else						DrawGraph((int)stoneInfo[i].x - 31, (int)stoneInfo[i].y - 32, stone_red,    TRUE);
	}
}

void Game() {
	switch (course) {
	case -3:
		sX = 60;
		sY = 520;
		xBevel = -3;
		yBevel = 10.5;
		break;
	case -2:
		sX = 100;
		sY = 530;
		xBevel = -2;
		yBevel = 10.75;
		break;
	case -1:
		sX = 140;
		sY = 540;
		xBevel = -1;
		yBevel = 11;
		break;
	case 0:
		sX = 180;
		sY = 540;
		xBevel = 0;
		yBevel = 8;
		break;
	case 1:
		sX = 220;
		sY = 540;
		xBevel = 1;
		yBevel = 11;
		break;
	case 2:
		sX = 260;
		sY = 530;
		xBevel = 2;
		yBevel = 10.75;
		break;
	case 3:
		sX = 300;
		sY = 520;
		xBevel = 3;
		yBevel = 10.5;
		break;

	}
	sX += 480;
	if (key[KEY_INPUT_ESCAPE] == 1)	gamemode = 2;
	
	for (int l = 0; l < 8; l++) {
		Shoot(l);
		Acceleration(l);
		StopLowStone(l);
		StopOverStone(l);
		PhysicStone(l);
		if (turnEndFlag)	gamecnt++;
	}
}

void DrawGame() {
	DrawGraph(481, 0, sheet, FALSE);
}

/*void MoveYellowStone(int i) {
	if (key[KEY_INPUT_Q] == 1) {
		yellowStone[i].x = 660;
		yellowStone[i].y = 100;
		setFlag = true;
	}
	if (key[KEY_INPUT_E] == 1 && setFlag) {
		moveFlag = true;
		speed = (double)power / 1.25;
		stoneMoveTime = cnt;
	}

	if (moveFlag) {
		nowStonePos += speed;
		yellowStone[i].x = 660 + sin(Rad(course * 2.5)) * nowStonePos;
		yellowStone[i].y = 100 + cos(Rad(course * 2.5)) * nowStonePos;
	}

	if (cnt % 20 == 0 && moveFlag) {
		speed *= 0.9;
	}

	if (speed < 0.2 && cnt - stoneMoveTime > 60) {
		moveFlag = false;
		nowStonePos = 0;
		speed = 0;
		turnEndFlag = true;
	}

	if (yellowStone[i].y > 740) {
		yellowStone[i].x = yellowStoneDefault[i].x;
		yellowStone[i].y = yellowStoneDefault[i].y;
		setFlag = false;
		//moveFlag = false;
		nowStonePos = 0;
		turnEndFlag = true;
	}
}*/

/*void MoveRedStone(int i) {
	i--;
	if (key[KEY_INPUT_Q] == 1) {
		redStone[i].x = 660;
		redStone[i].y = 100;
		setFlag = true;
	}
	if (key[KEY_INPUT_E] == 1 && setFlag) {
		moveFlag = true;
		speed = (double)power / 1.25;
		stoneMoveTime = cnt;
	}

	if (moveFlag) {
		nowStonePos += speed;
		redStone[i].x = 660 + sin(Rad(course * 2.5)) * nowStonePos;
		redStone[i].y = 100 + cos(Rad(course * 2.5)) * nowStonePos;
	}

	if (cnt % 20 == 0 && moveFlag) {
		speed *= 0.9;
	}

	if (speed < 0.2 && cnt - stoneMoveTime > 60) {
		moveFlag = false;
		nowStonePos = 0;
		speed = 0;
		turnEndFlag = true;
	}

	if (redStone[i].y > 740) {
		redStone[i].x = redStoneDefault[i].x;
		redStone[i].y = redStoneDefault[i].y;
		setFlag = false;
		moveFlag = false;
		nowStonePos = 0;
		turnEndFlag = true;
	}
}*/

void Shoot(int i) {
	if (key[KEY_INPUT_Q] == 1) {
		stoneInfo[i].x = 660;
		stoneInfo[i].y = 100;
		setFlag = true;
	}
	if (key[KEY_INPUT_E] == 1 && setFlag) {
		moveFlag = true;
		stoneInfo[i].speed = (double)power / 1.25;
		stoneMoveTime = cnt;
	}
}

void Acceleration(int i) {
	if (moveFlag) {
		nowStonePos += stoneInfo[i].speed;
		stoneInfo[i].x = 660 + sin(Rad(course * 2.5)) * nowStonePos;
		stoneInfo[i].y = 100 + cos(Rad(course * 2.5)) * nowStonePos;
	}

	if (cnt % 20 == 0 && moveFlag) {
		stoneInfo[i].speed *= 0.9;
	}
}

void StopLowStone(int i) {
	for (int l = 0; l < 8; l++) {
		if (stoneInfo[i].speed < 0.2 && cnt - stoneMoveTime > 60) {
			moveFlag = false;
			nowStonePos = 0;
			stoneInfo[i].speed = 0;
			turnEndFlag = true;
		}
	}
}

void StopOverStone(int i) {
	for (int l = 0; l < 8; l++) {
		if (stoneInfo[i].y > 740) {
			stoneInfo[i].x = stoneDefault[i].x;
			stoneInfo[i].y = stoneDefault[i].y;
			setFlag = false;
			moveFlag = false;
			nowStonePos = 0;
			turnEndFlag = true;
		}
	}
}

void PhysicStone(int i) {

}


//Debug

void DrawInfo() {
	DrawFormatStringToHandle(0, 20, 0x000000, Cica16, "course:%d,power:%d\nspeed:%f,nowStonePos:%f\nsetFlag:%s,moveFlag:%s", course, power, speed, nowStonePos, setFlag?"true":"false", moveFlag?"true":"false");
}

void DrawMousePos() {
	DrawFormatStringToHandle(0, 0, 0x000000, Cica16, "X: %d Y: %d", mX, mY);
}

void DrawShootLine() {
	DrawLineAA((float)660, (float)100, (float)sX, (float)sY, 0x000000, (float)4);
}

void DrawShootLineRad() {
	DrawLineAA((float)660, (float)100, (float)660 + (float)sin(Rad(course * 2.5)) * (float)300, (float)100 + (float)cos(Rad(course * 2.5)) * (float)300, 0xff0000, 4);
}

/*void MoveStoneD(int cnt) {
	if (key[KEY_INPUT_Q] == 1) {
		yellowStone[cnt - 1].x = 660;
		yellowStone[cnt - 1].y = 100;
		setFlag = true;
	}
	if (key[KEY_INPUT_E] == 1 && setFlag) {
		moveFlag = true;
		speed = (double)power / 1.25;
		stoneMoveTime = cnt;
	}
	
	if (moveFlag) {
		nowStonePos += speed;
		yellowStone[cnt - 1].x = 660 + sin(Rad(course * 2.5)) * nowStonePos;
		yellowStone[cnt - 1].y = 100 + cos(Rad(course * 2.5)) * nowStonePos;
	}
	
	if (cnt % 20 == 0 && moveFlag) {
		speed *= 0.9;
	}

	if (speed < 0.2 && cnt - stoneMoveTime > 60) {
		moveFlag = false;
		nowStonePos = 0;
		speed = 0;
	}
}*/

double Rad(int deg) {
	return (double)deg * PI / 180;
}