#include<vector>
using namespace std;
#include "Headers/Global.h"
#include "Headers/Cell.h"
#include "Headers/GetCell.h"

Cell* getCell(int _x, int _y, int diff, vector<Cell>& _cells)
{
	return &_cells[_x + static_cast<std::vector<Cell, std::allocator<Cell>>::size_type>(_y) * BOARD_HEIGHT[diff]];
}