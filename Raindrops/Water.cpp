#include "Water.h"

Water::Water() { this->CreateWater(); }

Water::Water(const Water & w) { setUp(w); }

Water& Water::operator=(const Water& w) {
	this->waterMatrix.clear();
	setUp(w);
	return *this;
}

void Water::setUp(const Water & w) {
	waterLevel = w.waterLevel;
	moves = w.moves;
	min_waterLevel = w.min_waterLevel;
	waterMatrix = w.waterMatrix;
}

void Water::CreateWater(int waterLevel) {
	for (int i = 0; i < 24; i++) {
		this->waterMatrix.resize(24);
		for (int j = 0; j < 24; j++) {
			this->waterMatrix[i].resize(24);
			this->waterMatrix[i][j] = 9;
		}
	}
}

void Water::SetWaterLevel() { 
	this->waterLevel -= 2; 
}

int Water::GetMoves() { 
	return this->moves; 
}

void Water::InsertWater(vector<vector<int>> &Matrix) {
	int len0 = this->min_waterLevel - this->waterLevel - 1;
	for (int i = this->waterLevel; i < 24; i++)
		for (int j = 1; j < 24; j++)
			Matrix[i][j] = waterMatrix[this->min_waterLevel - i - 1][j];
}