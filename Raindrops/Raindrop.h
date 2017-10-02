#pragma once
#include <vector>
#include <string>

using namespace std;

class Raindrop {
private:
	int x;
	int y;
	char operation = '0';
	vector<vector<int>> img;

public:
	Raindrop();
	Raindrop(const Raindrop&);

	void setUp(const Raindrop&);
	Raindrop& operator =(const Raindrop&);
	int GetResult();
	void SetOperation(int x, int y, char operation);
	string GetOperation();
	void InsertRB(vector<vector<int>> &Matrix, int position);
	
	~Raindrop() {}
};