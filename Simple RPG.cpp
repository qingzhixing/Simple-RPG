﻿#include <iostream>
#include <Windows.h>
#include"ConsoleDisplayController.h"
#include "GameController.h"

ConsoleDisplayController console = ConsoleDisplayController();
GameController game;

// 初始化
void Initialize() {
	console.ConsoleInitialize();
	console.onConsoleSizeChanged = []()->void {
		printf("OnConsoleSizeChanged\n");
		};
}

//游戏循环
void Frame() {
	DWORD startTime = GetTickCount();

	console.UpdateScreenBufferSize();

	game.Update();
	game.Draw();

	console.RefreshFrame();

	DWORD endTime = GetTickCount();
	DWORD deltaTime = endTime - startTime;

	// 锁定刷新率60fps
	if (deltaTime < 1000 / 60) {
		Sleep(1000 / 60 - deltaTime);
	}

	endTime = GetTickCount();
	deltaTime = endTime - startTime;

	// 显示fps
	wchar_t fpsDisplayStr[120] = {};
	swprintf(fpsDisplayStr, 100, L"FPS: %.2f", 1 / float(deltaTime) * 1000);
	SetConsoleTitle(fpsDisplayStr);
}

int main()
{
	std::cout << "Hello World!\n";
	Initialize();
	while (true) {
		Frame();
	}
}