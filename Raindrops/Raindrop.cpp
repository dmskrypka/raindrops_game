#include "Raindrop.h"

Raindrop::Raindrop(const Raindrop & rd) { setUp(rd); }

Raindrop& Raindrop::operator =(const Raindrop& rd) {
	this->img.clear();
	setUp(rd);
	return *this;
}

void Raindrop::setUp(const Raindrop & rd) {
	x = rd.x;
	y = rd.y;
	operation = rd.operation;
	img = rd.img;
}

Raindrop::Raindrop() {
	for (int i = 0; i < 8; i++) {
		this->img.resize(8);
		for (int j = 0; j < 7; j++) {
			this->img[i].resize(7);
			if (i == 0 && j == 3) {
				this->img[i][3] = 2;
			}
			else if (i >0) {
				if (i < 3) {
					if (j<2 || j>4) this->img[i][j] = 0;
					else this->img[i][j] = 2;
				}
				else if (i == 3 || i == 7) {
					if (j == 0 || j == 6) this->img[i][j] = 0;
					else this->img[i][j] = 2;
				}
				else {
					if (i != 5) this->img[i][j] = 2;
					else {
						if (j == 0 || j == 6) this->img[i][j] = 2;
						else this->img[i][j] = j + 2;
					}
				}
			}
			else this->img[i][j] = 0;
		}
	}
}

int Raindrop::GetResult() {
	switch (this->operation)
	{
	case '+':
		return this->x + this->y;
		break;
	case '-':
		return this->x - this->y;
		break;
	case '*':
		return this->x * this->y;
		break;
	default:
		return NULL;
		break;
	}
}

void Raindrop::SetOperation(int x, int y, char operation) {
	this->x = x;
	this->y = y;
	this->operation = operation;
}

string Raindrop::GetOperation() {
	string text;
	if (this->operation == '0') return NULL;
	else {
		text = to_string(this->x);
		text += this->operation;
		text += to_string(this->y);
	}
	return text;
}

void Raindrop::InsertRB(vector<vector<int>> &Matrix, int position) {
	int row = 8;
	if (position != 1) Matrix[position - 1][row + 3] = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			Matrix[position][row] = img[i][j];
			row++;
		}
		position++;
		row = 8;
	}
}