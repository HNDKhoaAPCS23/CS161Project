#pragma once
class Board
{
	bool firstOpen;
	int gameState;
	int diff;
	default_random_engine random_engine;

	random_device random_device;
public:

	vector<Cell> cells;
	Board(int _x);
	
	int getGameState() const;
	int getNumberFlag();
	int getNumberMines(int _x, int _y); 
	
	bool getFirstOpen() const;
	bool getIsFlag(int _x, int _y);
	bool getIsMine(int _x, int _y);
	bool getIsOpen(int _x, int _y);
	bool getKeyboardState(int _x, int _y);

	void updateKeyboard(int _x, int _y, int state);
	void flagCell(int _x, int _y);
	void openCell(int _x, int _y);
	void changeDiff(int _diff);
	void restart();
};