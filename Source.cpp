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
	SetWindowText("DxCurling 配布版Ver2.0");
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);
	DxLib_Init();
	//CreateFontToHandle
	{

		azukiL32  = LoadFontDataToHandle("./fonts/azukiL32.dft", 0);
		azukiL24  = LoadFontDataToHandle("./fonts/azukiL24.dft", 0);
		azukiLB24 = LoadFontDataToHandle("./fonts/azukiLB24.dft", 0);
		azukiLB32 = LoadFontDataToHandle("./fonts/azukiLB32.dft", 0);
		Cica32    = LoadFontDataToHandle("./fonts/Cica32.dft", 0);
		Cica16    = LoadFontDataToHandle("./fonts/Cica16.dft", 0);
	}
	//LoadGraph
	{
		stone_red = LoadGraph("./pic/stone_red.png");
		stone_yellow = LoadGraph("./pic/stone_yellow.png");
		brush = LoadGraph("./pic/brush.png");
		sheet = LoadGraph("./pic/sheet.png");
		infoFrame = LoadGraph("./pic/infoFrame.png");
	}
	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	InitStones();
	gamecnt = 0;
	waitingForInput = true;
	while (!ProcessMessage() && UpdateKey() == 0) {
		ClearDrawScreen();
		//ここに書く
		GetMousePoint(&mX, &mY);
		DrawBox(0, 0, 1280, 720, 0xffffff, TRUE); //白背景
		//DrawMousePos();
		switch (gamemode) {
		case op:
			OP();
			break;

		case game:
			//Control();
			DrawGame();
			//DrawInfo();
			Control();

			cnt++;
			break;

		case pause:
			Pause();
			break;

		case ed:

			ED();
			break;

		default:
			Error();
			break;
		}
		if (gameExit)	break;
		ControlDescription();
		//DrawBrush();
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
