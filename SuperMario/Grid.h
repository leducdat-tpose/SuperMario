#pragma once

#include <vector>
#include "GameObject.h"

#define DEFAULT_CELL_WIDTH 16
#define DEFAULT_CELL_HEIGHT 16

class CUnit
{
	friend class Grid;

private:
	CGrid* grid;
	LPGAMEOBJECT obj;
	float x;
	float y;

	CUnit* prev;
	CUnit* next;

public:
	CUnit(CGrid* grid, LPGAMEOBJECT obj, float x, float y);

	void Move(float x, float y);
	LPGAMEOBJECT GetObj() { return this->obj; }
};

class CGrid
{
	int map_width;
	int map_height;

	int cell_width;
	int cell_height;

	int nums_col;
	int nums_row;

	vector<vector<CUnit*>> cells;

public:
	CGrid(int map_width, int map_height, int cell_width = DEFAULT_CELL_WIDTH, int cell_height = DEFAULT_CELL_HEIGHT);
	~CGrid();

	void Add(CUnit* unit);
	void Move(CUnit* unit, float x, float y); 
	void Get(D3DXVECTOR3 camPosition, vector<CUnit*>& listUnits); 

	void Out();
};

