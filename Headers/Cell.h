#pragma once
class Cell
{
	int x, y;
	int keyboardState;
	int diff;
	int numberMines;
	bool isFlagged;
	bool isOpen;
	bool isMine;
public:
	Cell(int _x, int _y, int _diff);

	bool getIsFlagged() const;
	bool getIsOpen() const;
	bool getIsMine() const;
	bool open(vector<Cell>& _cells);

	int getKeyboardState() const;
	int getNumberMines() const;

	void changeKeyboardState(int state);
	void countMinesAround(vector<Cell>& _cells);
	void flag();
	void reset();
	void setMine();
};