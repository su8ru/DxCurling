/*
カーリングっぽいミニゲームっぽいもの

作成：subaru2003
*/

#include <DxLib.h>
#include <stdio.h>
#include <math.h>
#include "define.h"
#include "function.h"
#include "resource.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowText("DxCurling");
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);
	DxLib_Init();
	//CreateFontToHandle
	{
		azukiL32  = CreateFontToHandle("あずきフォントL", 32, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		azukiL24  = CreateFontToHandle("あずきフォントL", 24, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		azukiL16  = CreateFontToHandle("あずきフォントL", 16, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		azukiLB32 = CreateFontToHandle("あずきフォントLB", 32, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		azukiLB24 = CreateFontToHandle("あずきフォントLB", 24, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		azukiLB16 = CreateFontToHandle("あずきフォントLB", 16, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		Cica32    = CreateFontToHandle("Cica", 32, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		Cica24    = CreateFontToHandle("Cica", 24, -1, DX_FONTTYPE_ANTIALIASING_4X4);
		Cica16    = CreateFontToHandle("Cica", 16, -1, DX_FONTTYPE_ANTIALIASING_4X4);
	}
	//LoadGraph
	{
		stone_red = LoadGraph("./pic/stone_red.png");
		stone_yellow = LoadGraph("./pic/stone_yellow.png");
		brush = LoadGraph("./pic/brush.png");
		sheet = LoadGraph("./pic/sheet.png");
	}
	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	while (!ProcessMessage()) {
		UpdateKey();
		ClearDrawScreen();
		//ここに書く
		GetMousePoint(&mX, &mY);
		Draw();
		DrawMousePos();
		switch (gamemode) {
		case 0:
			OP();
			break;

		case 1:
			Game();
			Control();
			DrawGame();
			DrawInfo();
			//DrawShootLine();
			DrawShootLineRad();
			//MoveStoneD();
			DrawStone();
			//MoveOverStone();
			cnt++;
			break;

		case 2:
			Pause();
			break;
		
		case 3:
			ED();
			break;
		default:
			Error();
			break;
		}
		DrawBrush();
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}