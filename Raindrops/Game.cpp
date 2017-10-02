#include "Game.h"

#define GAME_SPEED 300
#define SLEEP_BEFORE 1700 // sleep before start or end game	

char symbol;

Game::Game(const Game & g) { setUp(g); }

void Game::setUp(const Game & g) {
	playerName = g.playerName;
	infoPath = g.infoPath;
	M = g.M;
	rd = g.rd;
	W = g.W;
}

Game& Game::operator=(const Game & g) {
	setUp(g);
	return *this;
}

void Game::RandomOperation(Raindrop &rd) {
	int minusX = rand() % 1;
	int minusY = rand() % 1;
	int x = rand() % 100;
	int y = rand() % 100;
	if (minusX) x *= -1;
	if (minusY)y *= -1;
	char arr[3] = { '+','-','*' };
	char o = arr[rand() % 2];
	this->rd.SetOperation(x, y, o);
}

void Game::Input(vector<vector<int>> &matrix, Raindrop &rd, GameMatrix &GM, int &nextDrop)
{
	if (_kbhit()) // catching symbol
	{
		switch (_getch())
		{
		case 13:
			if (matrix[25][3]) {
				matrix[25][2] = 1; // check Enter press
				if (matrix[25][1] == this->rd.GetResult()) {
					GM.SetScore();
					nextDrop = 1;
				}
			}
			break;
		case 8:
			if (matrix[25][3]) {
				matrix[25][2] = -1; // check BackSpace press
				if (matrix[25][1] >= 10) matrix[25][1] /= 10;
				else matrix[25][3] = 0;
			}
			break;
		case 189:
		case 108:
		case 45:
			if (matrix[25][23] == 0)	matrix[25][23] = 1; //check minus (1 - pressed)
			break;
		case 48:
		case 96:
			if (!matrix[25][3]) { // check number before
				matrix[25][1] = 0;
				matrix[25][3] = 1;
				if (matrix[25][23]) matrix[25][1] *= -1; // checking minus
			}
			else matrix[25][1] *= 10; // adding new number
			break;
		case 49:
		case 97:
			if (!matrix[25][3]) {
				matrix[25][1] = 1;
				matrix[25][3] = 1;
				if (matrix[25][23]) matrix[25][1] *= -1; // checking minus

			}
			else {
				matrix[25][1] *= 10;
				matrix[25][1] += (matrix[25][23] ? -1 : 1);
			}
			break;
		case 50:
		case 98:
			if (!matrix[25][3]) {
				matrix[25][1] = 2;
				matrix[25][3] = 1;
				if (matrix[25][23]) matrix[25][1] *= -1;
			}
			else {
				matrix[25][1] *= 10;
				matrix[25][1] += (matrix[25][23] ? -2 : 2);
			}
			break;
		case 51:
		case 99:
			if (!matrix[25][3]) {
				matrix[25][1] = 3;
				matrix[25][3] = 1;
				if (matrix[25][23]) matrix[25][1] *= -1;
			}
			else {
				matrix[25][1] *= 10;
				matrix[25][1] += (matrix[25][23] ? -3 : 3);
			}
			break;
		case 52:
		case 100:
			if (!matrix[25][3]) {
				matrix[25][1] = 4;
				matrix[25][3] = 1;
				if (matrix[25][23]) matrix[25][1] *= -1;
			}
			else {
				matrix[25][1] *= 10;
				matrix[25][1] += (matrix[25][23] ? -4 : 4);
			}
			break;
		case 53:
		case 101:
			if (!matrix[25][3]) {
				matrix[25][1] = 5;
				matrix[25][3] = 1;
				if (matrix[25][23]) matrix[25][1] *= -1;
			}
			else {
				matrix[25][1] *= 10;
				matrix[25][1] += (matrix[25][23] ? -5 : 5);
			}
			break;
		case 54:
		case 102:
			if (!matrix[25][3]) {
				matrix[25][1] = 6;
				matrix[25][3] = 1;
				if (matrix[25][23]) matrix[25][1] *= -1;
			}
			else {
				matrix[25][1] *= 10;
				matrix[25][1] += (matrix[25][23] ? -6 : 6);
			}
			break;
		case 55:
		case 103:
			if (!matrix[25][3]) {
				matrix[25][1] = 7;
				matrix[25][3] = 1;
				if (matrix[25][23]) matrix[25][1] *= -1;
			}
			else {
				matrix[25][1] *= 10;
				matrix[25][1] += (matrix[25][23] ? -7 : 7);
			}
			break;
		case 56:
		case 104:
			if (!matrix[25][3]) {
				matrix[25][1] = 8;
				matrix[25][3] = 1;
				if (matrix[25][23]) matrix[25][1] *= -1;
			}
			else {
				matrix[25][1] *= 10;
				matrix[25][1] += (matrix[25][23] ? -8 : 8);
			}
			break;
		case 57:
		case 105:
			if (!matrix[25][3]) {
				matrix[25][1] = 9;
				matrix[25][3] = 1;
				if (matrix[25][23]) matrix[25][1] *= -1;
			}
			else {
				matrix[25][1] *= 10;
				matrix[25][1] += (matrix[25][23] ? -9 : 9);
			}
			break;
		}
	}
}

int Game::convertNum(char *buff) {
	int res = 0;
	for (int i = 0; (*buff) != ' '; i++) {
		if (!res) res = (*buff) - '0';
		else {
			res *= 10;
			res += (*buff) - '0';
		}
		buff++;
	}
	return res;
}

string Game::convertRes(char *buff) {
	string res = "", tmp = "";
	int test = 0;
	while (*buff != '\0' && *buff != '\r') {
		if (!test && isdigit(*buff)) tmp += *buff;
		else if (!test && *buff == ' ') test = 1;
		else if (test) res += *buff;
		buff++;
	};
	res = res + ": " + tmp + '\0';
	return res;
}

void Game::showPrevResult() {
	ifstream info(this->infoPath);
	const int len = 30;
	char buff[len];
	while (true) {
		if (!info.is_open()) {
			system("cls");
			cout << "File info.txt couldn't be open\n";
			cout << "\n\n\n\n\n\n\n\n\n\n\n";
		}
		else {
			int x = 0;
			system("cls");
			cout << "\n Previous results:\n\n";
			while (true && !info.eof()) {
				info.getline(buff, len);
				if (!x && buff[0] == '\0') {
					cout << "\t You will be first!\n";
					cout << "\n\n\n\n\n\n\n\n\n\n\n";
					break;
				}
				if (buff[0] == '\r') break;
				x += 1;
				cout << x;
				cout << ". " + convertRes(buff) + "\n";
			}
		}
		break;
	}
	info.close();
}

void Game::saveRes() {
	int score = this->M.GetScore();
	ifstream doc_out(this->infoPath);
	const int len = 30;
	char buff[len];
	string res = to_string(score)+" "+this->playerName;
	string text;
	while (true) {
		if (!doc_out.is_open()) {
			system("cls");
			cout << "File info.txt couldn't be open\n";
			cout << "\n\n\n\n\n\n\n\n\n\n\n";
		}
		else {
			int x = 0;
			while (true && !doc_out.eof()) {
				doc_out.getline(buff, len);
				if (!x) {
					x=(score >= convertNum(buff) ? 1 : 0);
					if (x) {
						text.insert(text.size(), res);
						text.insert(text.size(), "\r\n");
					}
				}
				text.insert(text.size(), buff);
				text.insert(text.size(), "\r\n");
			}
			if (!x) {
				text.insert(text.size(), res);
				text.insert(text.size(), "\r\n");
			}
		}
		break;
	}
	doc_out.close();
	
	ofstream doc_in;
	doc_in.open(this->infoPath);
	if (!doc_in.is_open()) {
		cout << "File info.txt couldn't be open\n";
	}
	else {
		doc_in.clear();
		doc_in << text;
	}
	doc_in.close();
}

void Game::startMenu() {
	int test = 0;
	int choose = 0;
	while (true) {
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t ";
		if (!test) {
			cout << "Welcome to game Raindrops :)";
			cout << "\n\n\t\t\t 1. Start game";
			cout << "\n\t\t\t 2. Best results";
			cout << "\n\t\t\t 3. Exit\n";
			cout << "\n\t\t\t Enter your choose: ";
			cin >> choose;
			switch (choose) {
			case 1:
				test += 1;
				break;
			case 2:
				showPrevResult();
				cout << "\n";
				system("pause");
				break;
			case 3:
				system("cls");
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t ";
				cout << "Goodbye! Hope see you soon :)";
				cout << "\n\n\n\n\n\n\n\n\n\n\n";
				Sleep(SLEEP_BEFORE);
				exit(0);
				break;
			default:
				system("cls");
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t ";
				cout << "Please enter correct choose: 1, 2 or 3. Thank you!";
				cout << "\n\n\n\n\n\n\n\n\n\n\n";
				system("pause");
				break;
			}
		}
		else if (test == 1) {
			cout << "Please enter your name: ";
			cin >> this->playerName;
			test += 1;
		}
		else if (test == 2) {
			cout << "Great!!! Let's start this game.\n";
			Sleep(SLEEP_BEFORE);
			break;
		}
		cout << "\n\n\n\n\n\n\n\n\n\n\n";
		system("cls");
	}
}

void Game::start() {
	int len0 = 26;
	int len1 = 25;
	startMenu();
	vector<vector<int>> &matrix = this->M.GetMatrix();

	int stopGame = 14; //line for stop game
	int start = 0; //game start line

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int clr = 2;
	//this->rd.SetOperation(2, 3, '+');
	RandomOperation(rd);
	do {
		system("cls");
		int nextDrop = 0;
		if (start<stopGame)start++;
		this->rd.InsertRB(matrix, start);
		this->W.InsertWater(matrix);
		int test = 0;
		int i = 0;
		for (; i < len0; i++) {
			int x = 3, y = 5;
			for (int j = 0; j < len1; j++) {
				if (matrix[i][j] == 8 && i == len0 - 1) {
					if (j == 0) cout << " Result:";
					if (j == 7) {
						SetConsoleTextAttribute(handle, FOREGROUND_RED);
						cout << "Score:";
					}
					if (j == 8) // write score
						cout << matrix[25][len1 - 1];
				}
				if (matrix[len0 - 1][3] && i == len0 - 1 && j == 1) // write result
					cout << matrix[len0 - 1][1];
				if (matrix[i][j] == 1 && i != len0 - 1) {
					SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
					cout << "*";
				}
				else if (matrix[i][j] == 2 || matrix[i][j] == 9 && i != len0 - 1) {
					SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
					cout << "*";
				}
				else if (matrix[i][j] == 11) cout << "";
				else if (i<len0 - 1) {
					string s = "";
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
					string text = this->rd.GetOperation();
					int x = text.length() - 2;
					switch (matrix[i][j]) {
					case 3: // writing operation
						cout << text;
						for (int j1 = j + 1; j1 < x + j + 2; j1++)
							matrix[i][j1] = 11;
						break;
					default:
						cout << " ";
						break;
					}
				}
				else cout << " ";
			}
			if (i == len0 - 1) cout << "\r\t";
			else cout << "\n";
		}
		Input(matrix, rd, M, nextDrop);
		Sleep(GAME_SPEED);
		if (start == stopGame) { // create new try and level water upping
			start = 0;
			stopGame -= 2;
			this->W.SetWaterLevel();
			this->M.BlunkMatrix();
			matrix = this->M.GetMatrix();
			RandomOperation(rd);
		}
		if (nextDrop) {  // create new try
			start = 0;
			this->M.BlunkMatrix();
			matrix = this->M.GetMatrix();
			RandomOperation(rd);
		}
		if (stopGame < 4) { // game over
			system("cls");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t  GAME OVER\n";
			cout << "\n\t\t\t\t" + this->playerName + " your score: ";
			cout << this->M.GetScore();
			cout << "\n\n\n\n\n\n\n\n\n\n\n";
			saveRes();
			system("pause");
			break;
		}
	} while (true);
}