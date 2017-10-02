#pragma once
#include "Raindrop.h"
#include "Water.h"
#include <vector>
#include <string>

using namespace std;

class GameMatrix {
private:
	vector<vector<int>> M;
	int score = 0;

public:
	GameMatrix();
	GameMatrix(const GameMatrix&);

	void setUp(const GameMatrix&);
	GameMatrix& operator =(const GameMatrix&);
	void BlunkMatrix(int len0 = 26, int len1 = 25);
	vector<vector<int>> GetMatrix();
	void SetScore();
	int GetScore();

	~GameMatrix() {}
};