#include<iostream>
#include<stdio.h>
#include <chrono>
#include <thread>
#include<cstring>
#include<string>
#include<conio.h>
#include<vector>
#include <Windows.h>
#include<random>
#include<fstream>
using namespace std;
#include "Headers/console/console.h"
#include "Headers/Global.h"
#include "Headers/Cell.h"
#include "Headers/GetCell.h"
#include "Headers/Board.h"
struct Player
{
	int x, y;
	Player() : x(0), y(0){}
	void reset()
	{
		x = y = 0;
	}
};
struct Display
{
	int color;
	char thing;
	Display() : color(15), thing(' ') {}
	Display(int _color, char _thing)
	{
		color = _color;
		thing = _thing;
	}
};

Display buffer[CONSOLE_WIDTH+1][CONSOLE_HEIGHT+1];
Board board(0);
Player player;
bool inGame = 0;
int diff = 0;

void resetBuffer();
void updateBuffer(int x, int y, int color, char thing);
void show();
void drawCell(int x, int y, int color, char thing);
void drawBoard();
void drawText(int x, int y, int color, string& text);
void drawInfo();
void drawClock(int x, int y, int timer, int color);

int main()
{
	HANDLE hStdOut = NULL;
	CONSOLE_CURSOR_INFO curInfo;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hStdOut, &curInfo);
	curInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &curInfo);
	string notice;
	int counter = 0;
	int timer = 0;
	while (true)
	{
		if (inGame == 0)
		{
			notice = "Please choose a difficulty";
			drawText((CONSOLE_WIDTH - (int)notice.size()) / 2, CONSOLE_HEIGHT / 2 - 3, 15, notice);

			notice = "1. 8 x 8 (10 mines)";
			drawText((CONSOLE_WIDTH - (int)notice.size()) / 2, CONSOLE_HEIGHT / 2 - 2, 15, notice);

			notice = "2. 16 x 16 (40 mines)";
			drawText((CONSOLE_WIDTH - (int)notice.size()) / 2, CONSOLE_HEIGHT / 2 - 1, 15, notice);

			notice = "3. 25 x 25 (99 mines)";
			drawText((CONSOLE_WIDTH - (int)notice.size()) / 2, CONSOLE_HEIGHT / 2, 15, notice);
			
			if (_kbhit())
			{
				char key = _getch();
				if (key == '1')
				{
					diff = 0;
					board.changeDiff(diff);
					player.reset();
					timer = counter = 0;
					inGame = 1;
				}
				if (key == '2')
				{
					diff = 1;
					board.changeDiff(diff);
					player.reset();
					timer = counter = 0;
					inGame = 1;
				}
				if (key == '3')
				{
					diff = 2;
					board.changeDiff(diff);
					player.reset();
					timer = counter = 0;
					inGame = 1;
				}
			}
		}
		if (inGame == 1)
		{
			if (board.getGameState() == 0)
			{
				if (_kbhit())
				{
					char key = _getch();
					if (key == ARROW_DOWN || key == 's' || key == 'S')
					{
						if (player.y < BOARD_HEIGHT[diff] - 1)
						{
							board.updateKeyboard(player.x/2, player.y, 0);
							player.y++;
							board.updateKeyboard(player.x/2, player.y, 1);
						}
					}
					else if (key == ARROW_UP || key == 'w' || key == 'W')
					{
						if (player.y > 0)
						{
							board.updateKeyboard(player.x/2, player.y, 0);
							player.y--;
							board.updateKeyboard(player.x/2, player.y, 1);
						}
					}
					else if (key == ARROW_LEFT || key == 'a' || key == 'A')
					{
						if (player.x - 2 >= 0)
						{
							board.updateKeyboard(player.x/2, player.y, 0);
							player.x -= 2;
							board.updateKeyboard(player.x/2, player.y, 1);
						}
					}
					else if (key == ARROW_RIGHT || key == 'd' || key == 'D')
					{
						if (player.x + 2 < 2 * BOARD_WIDTH[diff]) 
						{
							board.updateKeyboard(player.x/2, player.y, 0);
							player.x += 2;
							board.updateKeyboard(player.x/2, player.y, 1);
						}
					}
					else if (key == 'X' || key == 'x')
					{
						board.openCell(player.x/2, player.y);
					}
					else if ((key == 'c' || key == 'C')&&(board.getFirstOpen() == 1))
					{
						if(!board.getIsFlag(player.x/2, player.y) && board.getNumberFlag() > 0)
							board.flagCell(player.x/2, player.y);
						else if(board.getIsFlag(player.x / 2, player.y))
							board.flagCell(player.x / 2, player.y);
					}
					/*
						x - open
						c - flag/unflag
					*/
				}
				board.updateKeyboard(player.x/2, player.y, 1);
				if (board.getFirstOpen() == 1)
				{
					++counter;
					if (counter == 10)
					{
						++timer;
						counter = 0;
					}
				}
				drawBoard();
				drawInfo();
				drawClock(2 * BOARD_WIDTH[diff] + 1, 6, timer, 232);
			}
			if (board.getGameState() != 0)
			{
				if (_kbhit())
				{
					char key = _getch();
					if (key == 'x' || key == 'X')
					{
						inGame = 0;
						resetBuffer();
					}
				}
				drawBoard();

				if (board.getGameState() == 1)
				{
					notice = "YOU WIN! PLEASE PRESS X TO CONTINUE PLAYING!";
					drawClock(0, BOARD_HEIGHT[diff] + 1, timer, 40);
					drawText(0, BOARD_HEIGHT[diff] + 2, 40, notice);
				}
				if (board.getGameState() == -1)
				{
					notice = "YOU LOSE! PLEASE PRESS X TO CONTINUE PLAYING!";
					drawText(0, BOARD_HEIGHT[diff] + 1, 195, notice);
				}
			}
		}
		show();
	}
	return 0;
}

void resetBuffer()
{
	for (int x = 0; x < CONSOLE_WIDTH; ++x) for (int y = 0; y < CONSOLE_HEIGHT; ++y)
		buffer[x][y] = Display(15, ' ');
}
void updateBuffer(int x, int y, int color, char thing)
{
	buffer[x][y].color = color;
	buffer[x][y].thing = thing;
}
void show()
{
	for (int x = 0; x < CONSOLE_WIDTH; ++x) for (int y = 0; y < CONSOLE_HEIGHT; ++y)
	{
		gotoXY(x, y);
		TextColor(buffer[x][y].color);
		putchar(buffer[x][y].thing);
	}
	resetBuffer();
}
void drawCell(int x, int y, int color, char thing)
{
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			updateBuffer(x + j, y, color, thing);
			thing = ' ';
		}
	}
}
void drawBoard()
{
	for (int x = 0; x < BOARD_WIDTH[diff]; ++x)
		for (int y = 0; y < BOARD_HEIGHT[diff]; ++y)
		{
			if (board.getGameState() == 0)
			{
				if (board.getIsOpen(x, y) == 1)
				{
					if (board.getNumberMines(x, y) != 0)
						drawCell(2 * x, y, 234, board.getNumberMines(x, y) + '0');
					else
						drawCell(2 * x, y, 255, ' ');
				}
				else if (board.getIsFlag(x, y) == 1) drawCell(2 * x, y, 120, 'F');
				else drawCell(2 * x, y, (((x + y) % 2 == 0) ? 37 : 105), ' ');

				if (board.getKeyboardState(x, y) == 1)
				{
					drawCell(2 * x, y, 20, ' ');
					if (board.getIsOpen(x, y) == 1)
					{
						if (board.getNumberMines(x, y) != 0)
							drawCell(2 * x, y, 20, board.getNumberMines(x, y) + '0');
					}
					else if (board.getIsFlag(x, y) == 1) drawCell(2 * x, y, 20, 'F');

				}
			}
			else
			{
				if (board.getIsFlag(x, y) == 1)
				{
					if (board.getIsMine(x, y) == 1)
						drawCell(2 * x, y, 37, 'F');
					else
						drawCell(2 * x, y, 200, 'F');
				}
				else if (board.getNumberMines(x, y) != 0)
					drawCell(2 * x, y, 234, board.getNumberMines(x, y) + '0');
				else if (board.getIsMine(x, y) == 1)
				{
					drawCell(2 * x, y, 120, 'B');
				}
				else
					drawCell(2 * x, y, 255, ' ');
			}
		}
}
void drawText(int x, int y, int color, string& text)
{
	for (int i = 0; i < (int)text.size(); ++i)
		buffer[x + i][y] = Display(color, text[i]);
}
void drawInfo()
{
	string notice;
	int numFlag = board.getNumberFlag();
	notice = "Flags Remain: ";
	string numFlagStr = "";
	numFlagStr += char((numFlag / 10) + '0');
	numFlagStr += char((numFlag % 10) + '0');
	notice += numFlagStr;
	drawText(2 * BOARD_WIDTH[diff] + 1, 0, 232, notice);
	notice = "X - Open";
	drawText(2 * BOARD_WIDTH[diff] + 1, 2, 232, notice);
	notice = "C - Flag";
	drawText(2 * BOARD_WIDTH[diff] + 1, 3, 232, notice);
	notice = "WASD/ARROW - Move";
	drawText(2 * BOARD_WIDTH[diff] + 1, 4, 232, notice);
}
void drawClock(int x, int y, int timer, int color)
{
	string notice;
	notice = "Timer: ";
	string clock = to_string(timer);
	notice += clock;
	drawText(x, y, color, notice);
}