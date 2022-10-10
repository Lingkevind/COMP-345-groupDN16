#include "Player.h"


	Player::Player() {
		std::string playerName = "default";
		pid = -1;
	};

	Player::Player(std::string newName, int newPid) {
		playerName = newName;
		pid = playerNum++;
	
	}
	Player::Player(const Player &copyPlayer) {
		playerName = copyPlayer.playerName;
		pid = playerNum++;
		playerOccupied = copyPlayer.playerOccupied;
		*playerHand = *(copyPlayer.playerHand);
	}
	Player::Player(std::string newName, int newPid, std::vector <Territory> newplayerOccupied, Hand h) {
		playerName = newName;
		pid = playerNum++;
		playerOccupied = newplayerOccupied;
		*playerHand = h;
		Order playerOrderlist(2);
	}
	
		
	vector <Territory> Player::toDefend() {

		std::vector <Territory>  toDefendVector;
		//toDefendVector = playerOccupied;
		Territory t1("t01");
		Territory t2("t02");
		Territory t3("t03");
		Territory t4("t04");
		toDefendVector.push_back(t1);
		toDefendVector.push_back(t2);
		toDefendVector.push_back(t3);
		toDefendVector.push_back(t4);
		return toDefendVector;
	}
	vector <Territory>Player::toAttack () {
		std::vector <Territory> toAttackVector;
		Territory t5("t05");
		Territory t6("t06");
		Territory t7("t07");
		Territory t8("t08");
		toAttackVector.push_back(t5);
		toAttackVector.push_back(t6);
		toAttackVector.push_back(t7);
		toAttackVector.push_back(t8);
		return toAttackVector;
	}
	
	void Player::issueOrder()
	{
		Order newPlayerOrder(1);
		playerOrderlist=(playerOrderlist, newPlayerOrder);
		
	}

	void Player::attack(Player pd)
	{
	std::cout << playerName << "\tattack\t" << pd.playerName <<"\n";
	}
	
	void Player::occupy(Territory t) {
		playerOccupied.push_back(t);
		std::cout << playerName << " occupyed " << t.getName() << "!\n";
	}
	void Player::occupy(Player p) {
		int occNum = p.playerOccupied.size();
		for (size_t i = 0; i <occNum; i++)
		{
			Territory t = p.playerOccupied[i];
			playerOccupied.push_back(t);
		}
		//p.playerOccupied.swap(playerOccupied);
	}

	void Player::displayerOcc() {
		//int playerSize = playerOccupied.size();<< playerplSize
		std::cout << "Player " << getPlayerName() << " territory incoulding: \n";
		displayOcc(playerOccupied);
	}

	 void Player::displayOcc(vector <Territory> occVector) {
		//vector <Territory> newplayerOccupied to cout string
		//int occSize = occVector.size();
		for (size_t i = 0; i < occVector.size(); i++)
		{
			string tName = occVector[i].getName();
			std::cout << tName << "\n";
		}
	}
	void Player::setPlayerName(string newName) {
		if (newName.empty()) {
			std::cout << "emptyname";
		}else  playerName = newName;
	}
	std::string Player::getPlayerName() {
		std::string str = "def";
		str = playerName;
		//std::cout << "player name: " << str << "\n";
		return str;
	}

//