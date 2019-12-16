#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include"battle.h"
#include<vector>
#include<string>
#include <map>
using namespace std;

int MAX_BOAT_SIZE = 5;

Battle::Battle() {
	xSize = 10;
	ySize = 10;
	usrHits = 0;
	cpuHits = 0;

	exitMsg = "Game has ended early. Thanks for playing!";

	for (int i = 0; i < ySize; i++) {
		vector<int> temp;

		for (int j = 0; j < xSize; j++) {
			temp.push_back(0);
		}

		usrBoard.push_back(temp);
		cpuBoard.push_back(temp);
		protectedBoard.push_back(temp);
	}
}

Battle::~Battle() {}

void Battle::start() {
	initBoard(usrBoard);
	initBoard(cpuBoard);

	char play = 'a';
	int c = 0;
	int x, y;

	while (play != 'q' && !isGameover()) {
		cout << "Welcome to Battleship! Enter any key to play." << endl;
		cin >> play;

		while (c != 4 && !isGameover()) {				
			cout << "\n" << endl;
			cout << "Game Options:" << endl;
			cout << "" << endl;
			cout << "1. Enter an x and y coordinate to shoot at your opponent's board." << endl;
			cout << "2. Display your board." << endl;
			cout << "3. Display the computer's board." << endl;
			cout << "4. Quit the game." << endl;
			cout << "\n" << endl;
			cin >> c;

			if (!cin) {
				// user didn't input a number
				cin.clear(); // reset failbit
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //skip bad input
				// next, request user reinput
			}

			switch (c) {
				case 1:
					cout << "Enter coordinates:";
					cin >> x >> y;

					while (tryUsrHit((x - 1), (y - 1))) {
						if (isGameover()) {
							break;
						}

						cout << "Enter coordinates:" << endl;
						cin >> x >> y;
					}

					while (!isGameover() && tryCpuHit()) {}
					break;
				case 2:
					displayBoard(usrBoard);
					break;
				case 3:
					displayBoard(protectedBoard);
					break;
				case 4:
					play = 'q';
					break;
				case 5:
					cout << "CPU HITS:" << endl;
					cout << cpuHits << endl;
				default:
					c = 0;
					break;
			}
		}
	}

	cout << "***************************************" << endl;
	cout << exitMsg << endl;
	cout << "***************************************" << endl;
}


void Battle::initBoard(vector<vector<int>> &board) {
	int x, y, d;

	for (int i = MAX_BOAT_SIZE - 1; i > 0; i--) {
		bool isValidCoordinate = false;

		while (!isValidCoordinate) {
			isValidCoordinate = true;
			
			x = rand() % 10;
			y = rand() % 10;
			d = rand() % 2;

			if ((d==0) && (x + i < 10)) {
				for (int j = x; j <= x + i; j++) {
					if (board[j][y] == 1) {
						isValidCoordinate = false;
					}
				}
			} else if ((d == 1) && (y + i < 10)) {
				for (int k = y; k <= y + i; k++) {
					if (board[x][k] == 1) {
						isValidCoordinate = false;
					}
				}
			}	else {
				isValidCoordinate = false;
			}
		}

		if (d == 0) {
			for (int j = x; j <= (x + i); j++) {
				board[j][y] = 1;
			}
		} else if (d == 1) {
			for (int k = y; k <= (y + i); k++) {
				board[x][k] = 1;
			}
		}
	}
}

void Battle::displayBoard(vector<vector<int>> &board) {
	for(int i = 0; i < ySize; i++){
		for(int j = 0; j < xSize; j++){
			cout << board[j][i] << " ";
		}
		cout << endl;
	}
}

bool Battle::tryUsrHit(int x, int y) {
	bool isHit = false;
	string msg = "";

	switch(cpuBoard[x][y]) {
		case 0:
			msg = "*USER: Oops! It seems like you did not hit anything.";
			cpuBoard[x][y] = 2;
			protectedBoard[x][y] = 2;
			break;
		case 1:
			isHit = true;
			msg = "*USER: Nice hit! Continue shooting.";
			cpuBoard[x][y] = 3;
			protectedBoard[x][y] = 3;
			usrHits += 1;
			break;
		default:
			msg = "*USER: You have already made this shot. Choose another coordinate.";
			break;
	}
	
	cout << msg << endl << endl;
	return isHit;
}

bool Battle::tryCpuHit() {
	bool isHit;
	string msg = "";

	int x = rand() % 10;
	int y = rand() % 10;

	int huntStackSize = cpuHuntStack.size();

	if (huntStackSize > 0) {
		x = cpuHuntStack.back()['x'];
		y = cpuHuntStack.back()['y'];

		cpuHuntStack.pop_back();
	}

	switch(usrBoard[x][y]) {
		case 0:
			isHit = false;
			usrBoard[x][y] = 2;
			msg = "*CPU: The computer has missed. Shoot your shot.";

			break;
		case 1:
			isHit = true;
			usrBoard[x][y] = 3;
			cpuHits += 1;
			msg = "*CPU: The computer has hit one of your ships!.";

			if (x < xSize - 1) {
				map<char, int> point = {
					{ 'x', x + 1 },
					{ 'y', y },
				};
				cpuHuntStack.push_back(point);
			}

			if (x > 0) {
				map<char, int> point = {
					{ 'x', x - 1 },
					{ 'y', y },
				};
				cpuHuntStack.push_back(point);
			}

			if (y < ySize - 1) {
				map<char, int> point = {
					{ 'x', x },
					{ 'y', y + 1},
				};
				cpuHuntStack.push_back(point);
			}

			if (y > 0) {
				map<char, int> point = {
					{ 'x', x },
					{ 'y', y - 1 },
				};
				cpuHuntStack.push_back(point);
			}
			break;
		default:
			// allow program to re-run if cpu already tried this hit.
			isHit = true;
			break;
	}

	cout << msg << endl << endl;

	return isHit;
}

bool Battle::isGameover() {
	switch (usrHits) {
		case 14:
			exitMsg = "Congratulations! You sunk all of your enemy's ships!";
			return true;
		default:
			return false;
	}

	switch (cpuHits) {
		case 14:
			exitMsg = "Your enemy sunk all of your ships. You have lost.";
			return true;
		default:
			return false;
	}
}
