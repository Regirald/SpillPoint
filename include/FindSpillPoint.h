#ifndef FINDSPILLPOINT
#define FINDSPILLPOINT
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <list>
using namespace std;

//int findMin(vector<vector<int>>& grid, queue<pair<int,int>> q);

//void Raise_level(vector<vector<int>>& grid,vector<vector<pair<bool, int>>> &visited, int h);

void PrintQ( queue<pair<int,int>> q);

int findMaxValue( vector<vector<int>>& grid);

queue<pair<int, int>> UpdateFront(vector<vector<int>>& grid, queue<pair<int, int>> &q, queue<pair<int, int>> &qFront,int &h);

list<pair<int,int>>  propagateByLayer(vector<vector<int>>& grid, vector<vector<pair<bool, int>>> & visited, queue<pair<int, int>> &q, queue<pair<int, int>> &qFront,int &h);

list<pair<int,int>> Find_Spill_Point(vector<vector<int>> grid, int startX, int startY);


#endif