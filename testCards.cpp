#include "Hand.cpp"
#include<stdexcept>
using namespace std;
int main() {
	srand(time(NULL));
	cout << "Welcome to Warzone card system tester 1.0!\n=========================================";
	Deck d = Deck();
	cout << "\nDeck created";
	d.initialize();
	d.randomShuffle();
	cout << "\nDeck initialized";
	Hand one = Hand("one");
	Hand two = Hand("two");
	cout << "\nPlayer 1 and player 2 created";
	for (int i = 0; i < 5; i++) {
		one.drawFrom(d);
		two.drawFrom(d);
	}
	cout << "\nfive card has been drawn by each player\n=========================================\nPlease select ur action among the options:";
	cout << "\n1. examine deck state\n2. examine player 1's hand\n3. examine player 2's hand\n4. player 1 draws a card\n5. player 2 draws a card\n6. player 1 plays a card\n7. player 2 plays a card\n8. exit the program\n";
	try {
		int option;
		cin >> option;
		while (option != 8) {
			if (option == 1) {
				d.display();
			}
			else if (option == 2) {
				one.display();
			}
			else if (option == 3) {
				two.display();
			}
			else if (option == 4) {
				one.drawFrom(d);
			}
			else if (option == 5) {
				two.drawFrom(d);
			}
			else if (option == 6) {
				one.display();
				cout << "\nplease select the card you want to play\n";
				int index;
				cin >> index;
				cout << "please enter the target you want to play it on (For this test, you may enter anything)\n";
				string target;
				cin >> target;
				one.playCards(index - 1, target, d);
			}
			else if (option == 7) {
				two.display();
				cout << "\nplease select the card you want to play\n";
				int index;
				cin >> index;
				cout << "please enter the target you want to play it on (For this test, you may enter anything)\n";
				string targ;
				cin >> targ;
				two.playCards(index - 1, targ, d);
			}
			else if (option == 8) {
			}
			else {
				throw option;
				break;
			}
			cout << "\n=========================================\nPlease select ur action among the options:";
			cout << "\n1. examine deck state\n2. examine player 1's hand\n3. examine player 2's hand\n4. player 1 draws a card\n5. player 2 draws a card\n6. player 1 plays a card\n7. player 2 plays a card\n8. exit the program\n";
			cin >> option;
		}
	}
	catch (int opt) {
		cout << "This is not a valid input.\n";
	}
	cout << "Terminating the program, thanks for using.";
	return 0;
}