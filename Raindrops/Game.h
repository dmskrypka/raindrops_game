#pragma once
#include "GameMatrix.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
//#include <cstdlib> // Error: "system" is ambiguous

using namespace std;

class Game {
private:
	string playerName;
	string infoPath;
	GameMatrix M;
	Raindrop rd;
	Water W;

public:
	Game() { this->infoPath = "res\\info.txt"; }
	Game(const Game&);

	void setUp(const Game&);
	Game& operator=(const Game&);
	void RandomOperation(Raindrop &rd);
	void Input(vector<vector<int>> &matrix, Raindrop &rd, GameMatrix &GM, int &nextDrop);
	int convertNum(char *buff);
	string convertRes(char *buff);
	void showPrevResult();
	void startMenu();
	void start();
	void saveRes();

	~Game() {}
};