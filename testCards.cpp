#include "Hand.h"
using namespace std;

int main() {
	//Using srand to modify seed to time value inorder to make the rand generate different random value at rach run
	srand(time(NULL));
	//Calling testcards
	testCards();
	return 0;
}