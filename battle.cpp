// Juan Pablo Mantica
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include"battle.h"
#include<vector>
#include<string>
using namespace std;

int usrHits = 0;
int cmpHits = 0;

Battle::Battle() {
	xSize = 10;
	ySize = 10;
	exitMsg = "Game has ended early. Thanks for playing!";

	for (int i = 0; i < ySize; i++) {
		vector<int> temp;

		for (int j = 0; j < xSize; j++) {
			temp.push_back(0);
		}
		usrBrd.push_back(temp);
		cmpBrd.push_back(temp);
		blankBrd.push_back(temp);
	}
}

Battle::~Battle() {}

void Battle::start() {
	initBoard(usrBrd);
	initBoard(cmpBrd);

	char play = 'a';
	int c = 0;
	int x, y;

	while (play != 'q' && !checkGameover()) {
		cout << "Welcome to Battleship! Enter any key to play." << endl;
		cin >> play;

		while (c != 4 && !checkGameover()) {				
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
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
				// next, request user reinput
			}

			switch (c) {
				case 1:
					cout << "Enter coordinates:";
					cin >> x >> y;

					while (tryHit((x - 1), (y - 1))) {
						if (checkGameover()) {
							break;
						}

						cout << "Enter coordinates:" << endl;
						cin >> x >> y;
					}

					while (!checkGameover() && cmpHit()) {}
					break;
				case 2:
					displayBoard(usrBrd);
					break;
				case 3:
					displayBoard(cmpBrd);
					break;
				case 4:
					play = 'q';
					break;
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

	for (int i = 4; i > 0; i--) {
		bool isValidCoordinate = false;

		while (!isValidCoordinate) {
			isValidCoordinate = true;
			
			x = rand() % 10;
			y = rand() % 10;
			d = rand() % 2;

			if ((d==0) && (x + i < 10)) {
				for (int j = x; j <= x+i; j++) {
					if (board[j][y] == 1) {
						isValidCoordinate = false;
					}
				}
			} else if ((d == 1) && (y + i < 10)) {
				for (int k = y; k <= y+i; k++) {
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

bool Battle::tryHit(int x, int y) {
	bool isHit = false;
	string msg = "";

	switch(cmpBrd[x][y]){
		case 0:
			msg = "** Oops! It seems like you did not hit anything.";
			cmpBrd[x][y] = 2;
			blankBrd[x][y] = 2;
			break;
		case 1:
			isHit = true;
			msg = "** Nice hit! Continue shooting.";
			cmpBrd[x][y] = 3;
			blankBrd[x][y] = 3;
			usrHits += 1;
			break;
		default:
			msg = "** You have already made this shot. Choose another coordinate.";
			break;
	}
	
	cout << msg << endl << endl;
	return isHit;
}

bool Battle::cmpHit() {
	bool isHit;
	int cmpX = rand() % 10;
	int cmpY = rand() % 10;
	string msg = "";

	switch(usrBrd[cmpX][cmpY]) {
		case 0:
			isHit = false;
			usrBrd[cmpX][cmpY] = 2;
			msg = "** The computer has missed. Shoot your shot.";
			break;
		case 1:
			isHit = true;
			usrBrd[cmpX][cmpY] = 3;
			cmpHits += 1;
			msg = "** The computer has hit one of your ships!.";
			break;
	}

	cout << msg << endl << endl;

	return isHit;
}

bool Battle::checkGameover() {
	switch (usrHits) {
		case 14:
			exitMsg = "Congratulations! You have sunken all of your enemy's ships!";
			return true;
		default:
			return false;
	}

	switch(cmpHits) {
		case 14:
			exitMsg = "Your enemy has sunken all of your ships. You have lost.";
			return true;
		default:
			return false;
	}
}
