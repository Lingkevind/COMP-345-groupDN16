#include "GameEngine.h";
#include <iostream>
using namespace std;

inline void testGameStates() {
	StateController* sc = new StateController(new StartState);
	while (true)
	{
		sc->UpdateState();
	}

}


int main()
{
	testGameStates();
}
