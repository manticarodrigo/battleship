// Juan Pablo Mantica
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include "battle.h"
#include <unistd.h>
using namespace std;


int main() {
	Battle game;
	srand(time(0));
	game.addCarriers();
	game.Menu();

	return 0;
}
	
	
