#pragma once
#include <DxLib.h>
#include <math.h>
#include "define.h"
#include "DrawStringEx.h"

#define PI 3.141592653589793
#define GoalX 1088
#define GoalY 360


void putStone(int id, double posx, double posy, double distance, bool yellow) {
	stones[id].x = posx;
	stones[id].y = posy;
	stones[id].vx = 0;
	stones[id].vy = 0;
	stones[id].distance = distance;
	stones[id].isYellow = yellow;
	stones[id].enabled = false;
}

void InitStones() {
	putStone(0, 36,  156, 0, true);
	putStone(1, 36,  564, 0, false);
	putStone(2, 100, 156, 0, true);
	putStone(3, 100, 564, 0, false);
	putStone(4, 164, 156, 0, true);
	putStone(5, 164, 564, 0, false);
	putStone(6, 228, 156, 0, true);
	putStone(7, 228, 564, 0, false);
	score = 0;
}


//常時

void DrawBrush() {
	DrawGraph(mX - 10, mY - 110, brush, TRUE);
}

void Error() {
	DrawBox(460, 320, 840, 400, 0xff0000, TRUE);
	DrawFormatStringToHandle(464, 328, 0xffffff, Cica32, "エラーが発生しました。\n部員を呼んでください。");
}


//OP,Pause,ED,TLE

void OP() {
	DrawFormatStringToHandle(569, 320, 0x000000, azukiLB32, "DxCurling");
	if (key[KEY_INPUT_SPACE] == 1) {
		gamemode = game;
		gamecnt = 0;
		InitStones();
	}
}

void Pause() {
	DrawFormatStringToHandle(544, 344, 0x000000, azukiLB32, "ぽーずがめん");
	if (key[KEY_INPUT_SPACE] == 1)	gamemode = game;
	if (key[KEY_INPUT_ESCAPE] == 1) gameExit = true;
}

void ED() {
	DrawFormatStringToHandle(480, 300, 0x000000, azukiLB32, "終了！！！");
	DrawFormatStringToHandle(480, 360, 0x000000, azukiLB24, "結果は…");
	if (!score)					DrawFormatStringToHandle(480, 390, 0x000000, azukiLB32, "同点でした！！");
	else if (winnerIsYellow)	DrawFormatStringToHandle(480, 390, 0x000000, azukiLB32, "黄色チームが%d点で勝利！！", score);
	else						DrawFormatStringToHandle(480, 390, 0x000000, azukiLB32, "赤チームが%d点で勝利！！", score);
	if (key[KEY_INPUT_SPACE])	gameExit = true;

	if (key[KEY_INPUT_D] && key[KEY_INPUT_R]) {
		gamemode = op;
		gamecnt = 0;
		InitStones();
	}
}


//Game

void Control() {
	if		(key[KEY_INPUT_W])		angle--;
	else if (key[KEY_INPUT_S])		angle++;

	else if (key[KEY_INPUT_A] == 1) power--;
	else if (key[KEY_INPUT_D] == 1) power++;

	if (angle < -30) angle = -30;
	if (angle > 30)  angle = 30;
	if (power > 5)   power = 5;
	if (power < 1)   power = 1;

	if (key[KEY_INPUT_ESCAPE] == 1)	gamemode = pause;

	//DrawFormatStringToHandle(0, 96, 0x000000, Cica16, "動いてるstoneはありますか:%d\n", isMovingAnyStones() ? 1 : 0);
	if (!waitingForInput && !isMovingAnyStones()) {
			gamecnt++;
			waitingForInput = true;
	}
	if (waitingForInput && key[KEY_INPUT_Q] == 1 && !placed) {
		stones[gamecnt].x = 96;
		stones[gamecnt].y = 360;
		placed = true;
	}
	if (waitingForInput && key[KEY_INPUT_E] == 1 && placed) {
		placed = false;
		stones[gamecnt].vx = power * cos(Rad(angle)) * 1.7;
		stones[gamecnt].vy = power * sin(Rad(angle)) * 1.7;
		waitingForInput = false;
	}
	if (gamecnt >= 8) {
		gamemode = ed;
		DecideRank();
		CalculateRank();
	}

	PhysicStone();
	StopSlowStone();
	StopOverStone();
	DistanceFromGoal();
}

void DrawStone() {
	for (int i = 0; i < 8; i++) {
		if (!stones[i].enabled) {
			if (stones[i].isYellow)	DrawGraph((int)stones[i].x - 32, (int)stones[i].y - 31, stone_yellow, TRUE);
			else					DrawGraph((int)stones[i].x - 32, (int)stones[i].y - 31, stone_red, TRUE);
		}
	}
}

void DrawGame() {
	DrawGraph(0, 121, sheet, FALSE);
	DrawShootLineRad();
	//MoveStoneD();
	DrawStone();
	//MoveOverStone();
	DrawBox(0, 0, 1280, 121, 0xffffff, TRUE);
}

void ControlDescription() {
	DrawGraph(0, 601, infoFrame, false);

	switch (gamemode) {
	case op:
		DrawFormatStringToHandle	(9,   610, 0xcbcbcb, Cica16, "> 〃∩ ∧＿∧\n> ⊂⌒(   ･ω･) ＜Let's play!\n>   ＼_っ⌒/⌒c\n>       ⌒ ⌒");
		DrawFormatStringToHandleEx	(269, 610, 0xcbcbcb, Cica16, "> [b8b84e]SPACE[-] でゲームを始める");
		break;
	case game:
		DrawFormatStringToHandleEx	(9,   610, 0xcbcbcb, Cica16, "> [56c4ca]angle[-]: %d°\n> [56c4ca]power[-]: %d\n> [56c4ca]turn[-]:  %d\n\n> 〃∩ ∧＿∧\n> ⊂⌒(   ･ω･) ＜ぼくの居場所…\n>   ＼_っ⌒/⌒c\n>       ⌒ ⌒", angle, (int)power, gamecnt + 1);
		DrawFormatStringToHandleEx	(269, 610, 0xcbcbcb, Cica16, "> [b8b84e]Q[-]   でストーンを設置します\n> [b8b84e]W･S[-] で打つ方向（[56c4ca]angle[-]）を決めます\n> [b8b84e]A･D[-] で打つ強さ（[56c4ca]power[-]）を決めます\n> [b8b84e]E[-]   でストーンを発射します\n> [b8b84e]ESC[-] でポーズ");
		break;
	case pause:
		DrawFormatStringToHandle	(9,   610, 0xcbcbcb, Cica16, "> 〃∩ ∧＿∧\n> ⊂⌒(   ･ω･) ＜やめないで…\n>   ＼_っ⌒/⌒c\n>       ⌒ ⌒");
		DrawFormatStringToHandleEx	(269, 610, 0xcbcbcb, Cica16, "> [b8b84e]SPACE[-] でゲームに戻る\n> [b8b84e]ESC[-]   でゲームを終了");
		break;
	case ed:
		DrawFormatStringToHandle	(9,   610, 0xcbcbcb, Cica16, "> 〃∩ ∧＿∧\n> ⊂⌒(   ･ω･) ＜Thank you!\n>   ＼_っ⌒/⌒c\n>       ⌒ ⌒");
		DrawFormatStringToHandleEx	(269, 610, 0xcbcbcb, Cica16, "> お疲れ様でした！また遊んでくださいね♪\n> [b8b84e]SPACE[-] でゲームを終了\n\n> 制作: [6fd20c]subaru2003[-]\n> Special Thanks: [6fd20c]ibuki2003[-], [6fd20c]QCFium[-]");
		DrawFormatStringToHandleEx	(749, 610, 0xcbcbcb, Cica16, "使用フォント: \n・[b8b84e]あずきフォント [56c4ca]http://azukifont.com/ \n[-]・[b8b84e]Cica-Regular   [56c4ca]https://github.com/miiton/Cica/");
		break;
	}
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
		if (stones[i].x > 1312 || stones[i].y < 98 || stones[i].y > 632) {
			stones[i].x = 10000 + 1000 * i;
			stones[i].vx = 0;
			stones[i].vy = 0;
			stones[i].enabled = true;
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
			if (i == j)	break;
			if (Distance(stones[i].x - stones[j].x, stones[i].y - stones[j].y) <= 64) {
				t = atan2(stones[j].y - stones[i].y, stones[j].x - stones[i].x);
				v = Distance(stones[i].vx - stones[j].vx, stones[i].vy - stones[j].vx);
				vt = atan2(stones[i].vy - stones[j].vy, stones[i].vx - stones[j].vx);
				vV = v * cos(t - vt);

				//DrawLine(stones[i].x, stones[i].y, stones[i].x + vV * k * cos(t), stones[i].y + vV * k * sin(t), 0xff);
				//DrawLine(stones[j].x, stones[j].y, stones[j].x - vV * k * cos(t), stones[j].y - vV * k * sin(t), 0xff);

				AddForce(j,  vV * k * cos(t),  vV * k * sin(t));
				AddForce(i, -vV * k * cos(t), -vV * k * sin(t));

				// 磁石現象/吹っ飛び防止
				if (stones[i].x <= stones[j].x && stones[i].vx >= stones[j].vx)
				{ // もしiの方が左なのにも関わらずiの方が右方向に早かったら
					stones[j].vx += stones[i].vx * k;
					stones[i].vx *= (1 - k);
				}
				if (stones[i].x >= stones[j].x && stones[i].vx <= stones[j].vx)
				{ // もしiの方が右なのにも関わらずjの方が右方向に早かったら
					stones[i].vx += stones[j].vx * k;
					stones[j].vx *= (1 - k);
				}
				// 同じことをyに対しても...
				if (stones[i].y <= stones[j].y && stones[i].vy >= stones[j].vy) {
					stones[j].vy += stones[i].vy * k;
					stones[i].vy *= (1 - k);
				}
				if (stones[i].y >= stones[j].y && stones[i].vy <= stones[j].vy) {
					stones[i].vy += stones[j].vy * k;
					stones[j].vy *= (1 - k);
				}
			}
		}
	}
	// TODO:衝突の処理はココらへん
}

void DistanceFromGoal() {
	for (int i = 0; i < 8; i++) {
		stones[i].distance = Distance(GoalX - stones[i].x, GoalY - stones[i].y);
	}
}


void DecideRank() {
	for (int i = 0; i<8; i++) {
		rank[i] = i;
	}
	while (1) {
		bool f = false;
		for (int i = 0; i<7; i++) {
			if (stones[rank[i]].distance>stones[rank[i + 1]].distance) {
				int tmp = rank[i];
				rank[i] = rank[i + 1];
				rank[i + 1] = tmp;
				f = true;
			}
		}
		if (!f) {
			break;
		}
	}

}

void CalculateRank() {
	if (stones[rank[0]].enabled)	return;
	if (!stones[rank[0]].isYellow) {	//Redの勝利
		for (int i = 0; i < 5; i++) {
			winnerIsYellow = false;
			if (stones[rank[i]].isYellow || stones[rank[i]].enabled) {
				score = i;
				return;
			}
		}
		while (1);
	} else {		//Yellowの勝利
		for (int i = 0; i < 5; i++) {
			winnerIsYellow = true;
			if (!stones[rank[i]].isYellow || stones[rank[i]].enabled) {
				score = i;
				return;
			}
		}
		while (1);
	}
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
	DrawFormatStringToHandle(0, 20, 0x000000, Cica16, "angle:%d\nplaced:%d\nturn:%d\ninput_ok:%d\nscore:%d", angle, placed ? 1 : 0, gamecnt, waitingForInput ? 1 : 0, score);
}

void DrawRankData() {
	/*
	for (int i = 0; i < 8; i++) {
		DrawFormatStringToHandle(1000, i * 16, 0x000000, Cica16, "%d", rank[i]);
	}*/
}
void DrawDistanceData() {
	/*for (int i = 0; i < 8; i++) {
		DrawFormatStringToHandle(1048, i * 16, 0x000000, Cica16, "%f", stones[rank[i]].distance);
	}*/
}

void DrawMousePos() {
	DrawFormatStringToHandle(0, 0, 0x000000, Cica16, "X: %d Y: %d", mX, mY);
}

void DrawShootLineRad() {
	DrawLineAA((float)96, (float)360, (float)126 + (float)cos(Rad(angle)) * (float)power * 100, (float)360 + (float)sin(Rad(angle)) * (float)power * 100, 0x00ff00, 4);
}


//calculation

double Rad(int deg) {
	return (double)deg * PI / 180;
}

void AddForce(int id, double x, double y) {
	stones[id].vx += x;
	stones[id].vy += y;
}

double Distance(double x, double y) {
	return sqrt(x * x + y * y);
}
