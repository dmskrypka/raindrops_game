#include "GameMatrix.h"

GameMatrix::GameMatrix() { this->BlunkMatrix(); }

GameMatrix::GameMatrix(const GameMatrix & gm) { setUp(gm); }

GameMatrix& GameMatrix::operator =(const GameMatrix& gm) {
	this->M.clear();
	setUp(gm);
	return *this;
}

void GameMatrix::setUp(const GameMatrix & gm) {
	this->M = gm.M;
	this->score = gm.score;
}

void GameMatrix::BlunkMatrix(int len0, int len1) {
	for (int i = 0; i < len0; i++) {
		this->M.resize(len0);
		for (int j = 0; j < len1; j++) {
			this->M[i].resize(len1);
			if (i == len0 - 1) this->M[i][j] = 8;
			else if (i == 0 || i == len0 - 2 || j == 0 || j == len1 - 1) this->M[i][j] = 1;
			else this->M[i][j] = 0;
		}
	}
	this->M[25][3] = 0;
	this->M[25][23] = 0;
	this->M[25][len1 - 2] = 0;
	this->M[25][len1 - 1] = this->score;
}

vector<vector<int>> GameMatrix::GetMatrix() {
	return this->M; 
}

void GameMatrix::SetScore() {
	this->score += 10; 
}

int GameMatrix::GetScore() {
	return this->score; 
}