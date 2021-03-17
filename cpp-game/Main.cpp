#include <iostream>
#include <thread>
#include <vector>

#include <stdio.h>
#include <Windows.h>

int screenWidth = 120;
int screenHeight = 40;

void consoleDraw(HANDLE consoleHandle, wchar_t* scr, DWORD dwBW) {
	scr[screenWidth * screenHeight - 1] = '\0';
	WriteConsoleOutputCharacter(consoleHandle, scr, screenWidth * screenHeight, { 0, 0 }, &dwBW);
}

void drawChar(wchar_t* screen, char c, int x, int y) {
	screen[x * y] = c;
}

void draw(int x, int y, wchar_t* screen) {
	drawChar(screen, 'h', x, y);
}

int main()
{
	wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	HANDLE consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(consoleHandle);
	DWORD dwBytesWritten = 0;

	for (int i = 0; i < screenWidth * screenHeight; i++) {
		screen[i] = ' ';
	}

	while (1) {
		for (int y = 0; y < screenHeight; y++) {
			for (int x = 0; x < screenWidth; x++) {
				draw(x, y, screen);
			}
		}
		consoleDraw(consoleHandle, screen, dwBytesWritten);
	}

	return 0;
}
