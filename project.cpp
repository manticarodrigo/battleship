#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include "battle.h"
#include <unistd.h>
using namespace std;


int main() {
	// rand number generator algorithm seed 
	srand(time(0));
	// start battle
	Battle battle;
	battle.start();

	return 0;
}
