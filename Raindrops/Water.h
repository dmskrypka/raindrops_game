#pragma once
#include <vector>

using namespace std;

class Water {
private:
	int waterLevel = 21;
	int moves = 2;
	int min_waterLevel = 24;

	vector<vector<int>> waterMatrix;
public:
	Water();
	Water(const Water&);

	void setUp(const Water&);
	Water& operator=(const Water&);
	void CreateWater(int waterLevel = 21);
	void SetWaterLevel();
	int GetMoves();
	void InsertWater(vector<vector<int>> &Matrix);

	~Water() {}
};