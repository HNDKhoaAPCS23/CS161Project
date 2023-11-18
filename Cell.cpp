#include<vector>
using namespace std;
#include "Headers/console/console.h"
#include "Headers/Global.h"
#include "Headers/Cell.h"
#include "Headers/GetCell.h"
Cell::Cell(int _x, int _y, int _diff) :
	numberMines(0),
	x(_x),
	y(_y),
	diff(_diff)
{
	reset();
}
void Cell::reset()
{
	numberMines = 0;
	isFlagged = 0;
	isOpen = 0;
	isMine = 0;
	keyboardState = 0;
}
bool Cell::getIsFlagged() const {  return isFlagged; }
bool Cell::getIsOpen() const {  return isOpen; }
bool Cell::getIsMine() const { return isMine; }
int Cell::getKeyboardState() const { return keyboardState; }
void Cell::changeKeyboardState(int state)
{
	keyboardState = state;
}
bool Cell::open(vector<Cell>& _cells)
{
	if (isOpen == 0)
	{
		isOpen = 1;
		isFlagged = 0;
		if ((isMine == 0) && (numberMines == 0))
		{
			getCell(x, y, diff, _cells)->countMinesAround(_cells);
			for (int dx = -1; dx < 2; dx++) for (int dy = -1; dy < 2; dy++)
			{
				int newX = dx + x;
				int newY = dy + y;
				if ((dx == 0 && dy == 0) || (newX < 0 || newY < 0 || newX == BOARD_WIDTH[diff] || newY == BOARD_HEIGHT[diff]))
					continue;
				getCell(newX, newY, diff, _cells)->open(_cells);
			}
		}
	}
	return isMine;
}

int Cell::getNumberMines() const
{
	return numberMines;
}

void Cell::countMinesAround(vector<Cell>& _cells)
{
	numberMines = 0;
	if (isMine == 0)
	{
		for (int dx = -1; dx < 2; dx++) for (int dy = -1; dy < 2; dy++)
		{
			int newX = dx + x;
			int newY = dy + y;
			if ((dx == 0 && dy == 0) || (newX < 0 || newY < 0 || newX == BOARD_WIDTH[diff] || newY == BOARD_HEIGHT[diff]))
				continue;
			if (getCell(newX, newY, diff, _cells)->getIsMine() == 1) ++numberMines;
		}
	}
}
void Cell::flag()
{
	if (isOpen == 0) isFlagged = !isFlagged;
}
void Cell::setMine()
{
	isMine = 1;
}