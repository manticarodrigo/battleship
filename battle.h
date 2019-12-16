#include<map>
#include<vector>
#include<string>
using namespace std;

class Battle {
	public:
		Battle();
		~Battle();
		void start();
	private:
		int xSize;
		int ySize;
		int usrHits;
		int cpuHits;
		vector<map<char, int>> cpuHuntStack;
		vector<vector<int>> usrBoard;
		vector<vector<int>> cpuBoard;
		vector<vector<int>> protectedBoard;
		string exitMsg;
		void initBoard(vector<vector<int>> &board);
		void displayBoard(vector<vector<int>> &board);
		bool tryUsrHit(int, int);
		bool tryCpuHit();
		bool isGameover();
};
