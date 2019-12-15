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

void Battle::addCarriers()
{
int x, y, d;

for(int i = 4; i > 0; i--)
{
	bool check = false;
	while(!check){
		check=true;
		x=rand()%10;
		y=rand()%10;
		d=rand()%2;

		if((d==0) && (x+i<10)){
			for(int j = x; j <= x+i; j++)
				if(usrBrd[j][y] == 1)
					check=false;
		}
		else if((d==1) &&(y+i<10)){
			for(int k = y; k <= y+i; k++)
				if(usrBrd[x][k] == 1)
					check=false;
		}	
		else 
			check = false;
	}
	if(d==0)
		for (int j=x; j<=x+i; j++)
			usrBrd[j][y] = 1;
	else if(d==1)
		for (int k = y; k <= y+i; k++)
			usrBrd[x][k] = 1;
	check = false;

	while(!check){
		check=true;
		x=rand()%10;
		y=rand()%10;
		d=rand()%2;

		if((d==0) && (x+i<10)){
			for(int j = x; j <= x+i; j++)
				if(cmpBrd[j][y] == 1)
					check=false;
		}
		else if((d==1) &&(y+i<10)){
			for(int j = y; j <= y+i; j++)
				if(cmpBrd[x][j] == 1)
					check=false;
		}	
		else 
			check = false;
	}
	if(d==0)
		for (int j=x; j<=x+i; j++)
			cmpBrd[j][y] = 1;
	else if(d==1)
		for (int j = y; j <= y+i; j++)
			cmpBrd[x][j] = 1;
	}

}



bool Battle::Hit(int x, int y) {

	bool isHit = false;
	string msg = "";
	switch(cmpBrd[x][y]){
		case 0:
			msg = "Oops! It seems like you did not hit anything.";
			cmpBrd[x][y] = 2;
			blankBrd[x][y] = 2;
			break;
		case 1:
			isHit = true;
			msg = "Nice hit! Continue shooting.";
			cmpBrd[x][y] = 3;
			blankBrd[x][y] = 3;
			usrHits += 1;
			Display();
			break;
		default:
			msg = "You have already made this shot. Choose another coordinate.";
			break;
	}
	
	cout << msg << endl << endl;
	return isHit;
}

Battle::Battle()
{
	xSize=10;
	ySize=10;
	winMsg="a";
	string cmpHitMsg = "a";
	for(int i = 0; i < ySize;i++)
	{
		vector<int> temp;
		for(int j = 0; j < xSize; j++)
			temp.push_back(0);
		usrBrd.push_back(temp);
		cmpBrd.push_back(temp);
		blankBrd.push_back(temp);
	}
}

Battle::~Battle() {}

void Battle::Display()
{
	for(int i = 0; i < ySize; i++){
		for(int j = 0; j < xSize; j++){
			cout << usrBrd[j][i] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	for(int i = 0; i < ySize; i++){
		for(int j = 0; j < xSize; j++){
			cout << blankBrd[j][i] << " ";
		}
		cout << endl;
	}
}

void Battle::Menu() {
	int x, y;
	char play = 'a';
	int c = 0;
	while(play != 'q'){
		cout << "Welcome to Battleship! Press p to play!" << endl;
		cin >> play;

		switch(play){
			case 'p':
				while ( c!=4){				
					cout << "1. Enter an x and y coordinate to shoot at your opponent's board." << endl;
					cout << "2. Display your Board." << endl;
					cout << "3. Display the computer's board." << endl;
					cout << "4. Quit the game." << endl;
					cin >> c;

					switch(c){
						case(1):
						    cout << "Enter coordinates:";
							cin >> x >> y;
							while (Hit((x-1),(y-1))){
								if(Gameover())
									break;	
								cout << "Enter coordinates:" << endl;
								cin >> x >> y;
							}
							while(cmpHit()){
								if(Gameover())
									break;
							}
							break;
						case(2):
							for(int i = 0; i < ySize; i++){
								for(int j = 0; j < xSize; j++){
									cout << usrBrd[j][i] << " ";
								}
								cout << endl;
							}
							cout << endl;
							break;
						case(3):
							for(int k = 0; k < ySize; k++){
								for(int l = 0; l < xSize; l++){
									cout << blankBrd[l][k] << " ";
								}
								cout << endl;
							}
							cout << endl;
								break;

					}
				if (winMsg!="a"){
					cout << winMsg << endl << endl;
					winMsg = "a";
				}

			}
			
		}
	}
}

bool Battle::Gameover()
{
	switch(usrHits){
		case 14:
			winMsg = "Congratulations! You have sunken all of your enemy's ships!";
			for(int i = 0; i < ySize;i++)
				for(int j = 0; j < xSize; j++){
				usrBrd[i][j]=0;
				cmpBrd[i][j]=0;
				}
			usrHits = 0;
			addCarriers();
			return true;
		default:
			return false;
	}

	switch(cmpHits){
		case 14:
			winMsg = "Your enemy has sunken all of your ships. You have lost.";
			for(int i = 0; i < ySize;i++)
				for(int j = 0; j < xSize; j++){
				usrBrd[i][j]=0;
				cmpBrd[i][j]=0;
				}
			cmpHits = 0;
			addCarriers();
			return true;
		default:
			return false;
	}


}

bool Battle::cmpHit()
{
	
	int cmpX = rand()%10;
	int cmpY = rand()%10;
	bool isCmpHit;
	switch(usrBrd[cmpX][cmpY]){
		case 0:
			cmpHitMsg = "The computer has missed. Shoot your shot.";
			usrBrd[cmpX][cmpY] = 2;
			isCmpHit = false;
			Display();
			break;
		case 1:
			cmpHitMsg = "The computer has hit one of your ships!.";
			usrBrd[cmpX][cmpY] = 3;
			cmpHits += 1;
			isCmpHit = true;
			break;
	}
	cout << cmpHitMsg << endl << endl;
	
	return isCmpHit;
}
