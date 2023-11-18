#include<vector>
#include<random>
#include<iostream>
using namespace std;
#include "Headers/console/console.h"
#include "Headers/Cell.h"
#include "Headers/GetCell.h"
#include "Headers/Board.h"
#include "Headers/Global.h"

Board::Board(int _x) :
	random_engine(random_device())
{ 
	restart();
}
void Board::restart()
{
	firstOpen = 0;
	gameState = 0;
	for (Cell& cell : cells) cell.reset();
}
void Board::changeDiff(int _diff)
{
	diff = _diff;
	cells.clear();
	for (int i = 0; i < BOARD_WIDTH[diff]; ++i) for (int j = 0; j < BOARD_HEIGHT[diff]; ++j)
	{
		cells.push_back(Cell(j, i, diff));
	}
	restart();
}
int Board::getGameState() const
{
	return gameState;
}

int Board::getNumberFlag() 
{
	int numberFlags = 0;

	for (Cell& cell : cells)
		numberFlags += cell.getIsFlagged();
	return NUMBER_MINES[diff] - numberFlags;
}
void Board::flagCell(int _x, int _y)
{
	if (gameState == 0)
	{
		getCell(_x, _y, diff,cells)->flag();
	}
}
void Board::openCell(int _x, int _y)
{
	if (firstOpen == 0)
	{
		uniform_int_distribution<short> xDistribution(0, BOARD_WIDTH[diff] - 1);
		uniform_int_distribution<short> yDistribution(0, BOARD_HEIGHT[diff] - 1);
		
		firstOpen = 1;

		for (int i = 0; i < NUMBER_MINES[diff]; ++i)
		{
			int mineX = static_cast<short>(xDistribution(random_engine));
			int mineY = static_cast<short>(yDistribution(random_engine));

			if (getCell(mineX, mineY, diff, cells)->getIsMine() == 1 || ((_x == mineX) && (_y == mineY)))
			{
				--i;
			}
			else
			{
				getCell(mineX, mineY, diff, cells)->setMine();
			}
		}

		for (Cell& cell : cells)
			cell.countMinesAround(cells);
	}
	if (gameState == 0 && getCell(_x, _y, diff, cells)->getIsFlagged() == 0)
	{
		if (getCell(_x, _y, diff, cells)->open(cells) == 1)
		{
			gameState = -1;
		}
		else
		{
			int numberClosedCell = 0;
			for (Cell& cell : cells)
				numberClosedCell += 1 - cell.getIsOpen();
			if (numberClosedCell == NUMBER_MINES[diff])
			{
				gameState = 1;
			}
		}
	}
}
void Board::updateKeyboard(int _x, int _y, int state)
{
	getCell(_x, _y, diff, cells)->changeKeyboardState(state);
}
bool Board::getIsFlag(int _x, int _y) {  return (getCell(_x, _y, diff, cells)->getIsFlagged()); }
bool Board::getIsMine(int _x, int _y) {  return (getCell(_x, _y, diff, cells)->getIsMine()); }
bool Board::getIsOpen(int _x, int _y) {  return (getCell(_x, _y, diff, cells)->getIsOpen()); }
bool Board::getKeyboardState(int _x, int _y) { return (getCell(_x, _y, diff, cells)->getKeyboardState()); }
bool Board::getFirstOpen() const { return firstOpen; }
int Board::getNumberMines(int _x, int _y) {  return (getCell(_x, _y, diff, cells)->getNumberMines()); }

