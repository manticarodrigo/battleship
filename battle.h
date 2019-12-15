#include<vector>
#include<string>
using namespace std;

class Battle {
	public:
		Battle();
		~Battle();
		bool Hit(int, int);
		bool cmpHit();
		void Display();
		void addCarriers();
		void Menu();
		bool Gameover();
	private:
		int xSize;
		int ySize;
		vector<vector<int>> usrBrd;
		vector<vector<int>> cmpBrd;
		vector<vector<int>> blankBrd;
		string winMsg;
		string cmpHitMsg;
		bool isCmpHit;
};
