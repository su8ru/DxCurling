#pragma once
#include <DxLib.h>
#include <math.h>
#include "define.h"

#define PI 3.141592653589793


void putStone(int id, double posx, double posy, bool yellow) {
	stones[id].x = posx;
	stones[id].y = posy;
	stones[id].vx = 0;
	stones[id].vy = 0;
	stones[id].isYellow = yellow;
}

void InitStones() {
	putStone(0, 36,  156, true);
	putStone(1, 36,  564, false);
	putStone(2, 100, 156, true);
	putStone(3, 100, 564, false);
	putStone(4, 164, 156, true);
	putStone(5, 164, 564, false);
	putStone(6, 228, 156, true);
	putStone(7, 228, 564, false);
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
	if (key[KEY_INPUT_SPACE] == 1)	gamemode = game;

}

void Pause() {
	DrawFormatStringToHandle(544, 344, 0x000000, azukiLB32, "ぽーずがめん");
	if (key[KEY_INPUT_SPACE] == 1)	gamemode = game;
	if (key[KEY_INPUT_RETURN] == 1) {
		gamemode = op;
		gamecnt = 0;
		InitStones();
	}
}

void ED() {

}


void AddForce(int id, double x, double y) {
	stones[id].vx += x;
	stones[id].vy += y;
}

double Distance(double x, double y) {
	return sqrt(x * x + y * y);
}

//Game


void Control() {
	if (key[KEY_INPUT_A])		angle--;
	else if (key[KEY_INPUT_D])	angle++;

	else if (key[KEY_INPUT_S] == 1) power--;
	else if (key[KEY_INPUT_W] == 1) power++;

	if (angle<-30)angle = -30;
	if (angle>30)angle = 30;
	if (power>5)power = 5;
	if (power<1)power = 1;

	if (key[KEY_INPUT_ESCAPE] == 1)	gamemode = pause;

	printfDx("%d\n", isMovingAnyStones() ? 1 : 0);
	if (!waitingForInput && !isMovingAnyStones()) {
		gamecnt++;
		waitingForInput = true;
	}
	if (waitingForInput && key[KEY_INPUT_Q] == 1 && !placed) {
		stones[gamecnt].x = 660;
		stones[gamecnt].y = 100;
		placed = true;
	}
	if (waitingForInput && key[KEY_INPUT_E] == 1 && placed) {
		placed = false;
		stones[gamecnt].vx = power * sin(Rad(angle));
		stones[gamecnt].vy = power * cos(Rad(angle));
		waitingForInput = false;
	}

	PhysicStone();
	StopSlowStone();
	StopOverStone();
}


void DrawStone() {
	for (int i = 0; i < 8; i++) {
		if (stones[i].isYellow)	DrawGraph((int)stones[i].x - 32, (int)stones[i].y - 31, stone_yellow, TRUE);
		else					DrawGraph((int)stones[i].x - 32, (int)stones[i].y - 31, stone_red, TRUE);
	}
}


void DrawGame() {
	DrawGraph(0, 121, sheet, FALSE);
	DrawShootLineRad();
	//MoveStoneD();
	DrawStone();
	//MoveOverStone();

}



void StopSlowStone() {
	for (int i = 0; i < 8; i++) {
		if (stones[i].vx < 0.1 && stones[i].vy < 0.1) {
			nowStonePos = 0;
			stones[i].vx = 0;
			stones[i].vy = 0;
		}
	}
}

void StopOverStone() {
	for (int i = 0; i < 8; i++) {
		if (stones[i].y > 754) {
			stones[i].x = 10000 + 10000 * i;
			stones[i].vx = 0;
			stones[i].vy = 0;
			nowStonePos = 0;
		}
	}
}

void PhysicStone() {
	for (int i = 0;i<8;i++) {
		stones[i].x += stones[i].vx;
		stones[i].y += stones[i].vy;
		stones[i].vx *= 0.995;
		stones[i].vy *= 0.995;
	}
	double k = 0.9;
	double t, v, vt, vV;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == j)	continue;
			if (Distance(stones[i].x - stones[j].x, stones[i].y - stones[j].y) < 64) {
				t = atan2(stones[j].y - stones[i].y, stones[j].x - stones[i].x);
				v = Distance(stones[i].vx - stones[j].vx, stones[i].vy - stones[j].vx);
				vt = atan2(stones[i].vy - stones[j].vy, stones[i].vx - stones[j].vx);
				vV = v * cos(t - vt);

				DrawLine(stones[i].x, stones[i].y, stones[i].x + vV * k * cos(t), stones[i].y + vV * k * sin(t), 0xff);
				DrawLine(stones[j].x, stones[j].y, stones[j].x - vV * k * cos(t), stones[j].y - vV * k * sin(t), 0xff);

				AddForce(j, vV * k * cos(t), vV * k * sin(t));
				AddForce(i, -vV * k * cos(t), -vV * k * sin(t));
			}
		}
	}
	// TODO:衝突の処理はココらへん
}

bool isMovingAnyStones() {
	for (int i = 0;i < 8;i++) {
		if (stones[i].vx != 0 || stones[i].vy != 0) {
			return true;
		}
	}
	return false;
}


//Debug

void DrawInfo() {
	DrawFormatStringToHandle(0, 20, 0x000000, Cica16, "angle:%d\nplaced:%d\nturn:%d\ninput_ok:%d\n", angle, placed ? 1 : 0, gamecnt, waitingForInput ? 1 : 0);
}

void DrawMousePos() {
	DrawFormatStringToHandle(0, 0, 0x000000, Cica16, "X: %d Y: %d", mX, mY);
}

void DrawShootLine() {
	DrawLineAA((float)660, (float)100, (float)sX, (float)sY, 0x000000, (float)4);
}

void DrawShootLineRad() {
	DrawLineAA((float)660, (float)100, (float)660 + (float)sin(Rad(angle)) * (float)power * 100, (float)100 + (float)cos(Rad(angle)) * (float)power * 100, 0x00ff00, 4);
}


double Rad(int deg) {
	return (double)deg * PI / 180;
}
