#include<vector>
#include<string>
using namespace std;

class Battle {
	public:
		Battle();
		~Battle();
		void start();
		void initBoard(vector<vector<int>> &board);
		void displayBoard(vector<vector<int>> &board);
		bool tryHit(int, int);
		bool cmpHit();
		bool checkGameover();
	private:
		int xSize;
		int ySize;
		vector<vector<int>> usrBrd;
		vector<vector<int>> cmpBrd;
		vector<vector<int>> blankBrd;
		string exitMsg;
};
