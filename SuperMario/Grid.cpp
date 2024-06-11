#include "Grid.h"

Unit::Unit(Grid* grid, LPGAMEOBJECT obj, float x, float y)
{
	this->grid = grid;
	this->obj = obj;
	this->x = x;
	this->y = y;

	this->prev = NULL;
	this->next = NULL;

	grid->Add(this);
}

void Unit::Move(float x, float y)
{
	grid->Move(this, x, y);
}

Grid::Grid(int map_width, int map_height, int cell_width, int cell_height)
{
	this->map_width = map_width;
	this->map_height = map_height;

	this->cell_width = cell_width;
	this->cell_height = cell_height;

	nums_col = map_width / cell_width;
	nums_row = map_height / cell_height;

	cells.resize(nums_row);

	for (int i = 0; i < nums_row; i++)
		cells[i].resize(nums_col);

	for (int i = 0; i < nums_row; i++)
		for (int j = 0; j < nums_col; j++)
			cells[i][j] = NULL;
}

Grid::~Grid()
{
}

void Grid::Add(Unit* unit)
{
	int row = (int)(unit->y / cell_height);
	int col = (int)(unit->x / cell_width);

	unit->prev = NULL;
	unit->next = cells[row][col];
	cells[row][col] = unit;

	if (unit->next != NULL)
		unit->next->prev = unit;
}

void Grid::Move(Unit* unit, float x, float y)
{
	int old_row = (int)(unit->y / cell_height);
	int old_col = (int)(unit->x / cell_width);

	int new_row = (int)(y / cell_height);
	int new_col = (int)(x / cell_width);

	if (new_row < 0 || new_row >= nums_row || new_col < 0 || new_col >= nums_col)
		return;

	unit->x = x;
	unit->y = y;

	if (old_row == new_row && old_col == new_col)
		return;

	if (unit->prev != NULL)
	{
		unit->prev->next = unit->next;
	}

	if (unit->next != NULL)
	{
		unit->next->prev = unit->prev;
	}

	if (cells[old_row][old_col] == unit)
	{
		cells[old_row][old_col] = unit->next;
	}

	Add(unit);
}

void Grid::Get(D3DXVECTOR3 camPosition, vector<Unit*>& listUnits)
{
	int start_col = (int)(camPosition.x / cell_width);
	int end_col = (int)ceil((camPosition.x + SCREEN_WIDTH) / cell_width);

	for (int i = 0; i < nums_row; i++)
	{
		for (int j = start_col; j < end_col; j++)
		{
			Unit* unit = cells[i][j];

			while (unit != NULL)
			{
				if (unit->GetObj()->IsEnable() == true)
					listUnits.push_back(unit);

				unit = unit->next;
			}
		}
	}
}

void Grid::Out()
{
	for (int i = 0; i < nums_row; i++)
	{
		for (int j = 0; j < nums_col; j++)
		{
			int c = 0;
			Unit* unit = cells[i][j];

			while (unit)
			{
				c++;
				unit = unit->next;
			}
		}

	}
}


