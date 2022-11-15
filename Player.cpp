#include "Player.h"

	/// <summary>
	/// default player
	/// </summary>
	Player::Player() 
	{
		std::string playerName = "default";
		pid = -1;
	};
	/// <summary>
	/// at begin
	/// </summary>
	/// <param name="newName">at the begin of the game player must type their name</param>
	/// <param name="newPid">
	/// each player have their own pid
	/// so icreate static int playerNum = 0; for pid,
	///  when new player created playernum +1 and newplayer's pid = new playerNum
	/// </param>
	
	Player::~Player() {

	};

	Player::Player(std::string newName) 
	{
		playerName = newName;
		pid = playerNum++;
	}

	/// <param name="copyPlayer">copy constructer</param>
	Player::Player(const Player &copyPlayer)
	{
		this->playerName = copyPlayer.playerName;
		this->pid = playerNum++;
		this->playerOccupied = copyPlayer.playerOccupied;
		this->playerHand = (copyPlayer.playerHand);
		this->oList = copyPlayer.oList;
	}
	/// <summary>
	/// player playing the game
	/// </summary>
	/// playerOccupied show Territory occupyed by player
	/// 
	/// playerHand is a pointer point to player's hand
	/// 
	Player::Player(std::string newName, int newPid, std::vector <Territory*> newplayerOccupied, Hand h, int au)
	{
		playerName = newName;
		pid = newPid;
		playerOccupied = newplayerOccupied;
		*playerHand = h;
		Order *playerOrderlist = new Order;
		ArmyUnit = au;
	}

	bool Player::ownTerritory(Territory t) {
		if (find(playerOccupied.begin(), playerOccupied.end(), t) != playerOccupied.end()) {
			return true;
		}
		else {return false;
	}
	};
	
	/// <summary>
	/// method toDefend return a list of territories that are to be 
	/// defendedand to be attacked, respectively.
	/// will improve later
	/// </summary>
	/// <returns>a list of Territory that are owned by player</returns>
	vector <Territory> Player::toDefend()
	{

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
	/// <summary>
	/// method toAttack return a list of territories that are to be 
	/// defendedand to be attacked, respectively.
	/// will improve later
	/// </summary>
	/// <returns>a list of Territory player can attack</returns>
	vector <Territory>Player::toAttack () 
	{
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
	/// <summary>
	/// creat a order and add it to player's playerOrderlist
	/// </summary>
	void Player::issueOrder()
	{
		Order newPlayerOrder(1);
		playerOrderlist.push_back( newPlayerOrder);

	}
	
	void Player::attack(Player pd)
	{
	std::cout << playerName << "\tattack\t" << pd.playerName <<"\n";
	}

	void Player::leaveTerritory(Territory* t) {
		size_t occNum = playerOccupied.size();
		for (size_t i = 0; i < occNum; i++)
		{
			if (playerOccupied.at(i) == t)
			{
				//cout << "player "+ playerName + "leave Territory: "+ t->getName() + "\n";
				playerOccupied.erase(playerOccupied.begin()+i);
				return;
			} //else { cout << "not find t\n"; }
		}
		cout << "not find "+t->getName() + "in this player's playerOccupied\n";
	}	

	string Player::occupy(Territory* t) {
		this->playerOccupied.push_back(t);
		return playerName + " occupyed " + t->getName() + "!\n";
	}
	string Player::occupy(Territory* defeatedPlayerT, Player defeatedPlayer) {
		occupy(defeatedPlayerT);
		defeatedPlayer.leaveTerritory(defeatedPlayerT);
		return getPlayerName() + " occupyed " + defeatedPlayer.getPlayerName() + "!\n";
	}

	string Player::annex( Player *p){
		int occNum = p->playerOccupied.size();
		for (size_t i = 0; i <occNum; i++)
		{
			Territory* t = p->playerOccupied.at(i);
			playerOccupied.push_back(t);
		}
		p->playerOccupied.clear();
		return getPlayerName() + " annexation " + p->getPlayerName() + "!\n";
	}
	/// <summary>
	/// displayer player's info 
	/// will be delete later
	/// </summary>
	void Player::displayerOcc() { displayOcc(getplayerOccupied());}
	 /// <summary>
	 /// used to display Territory list
	 /// </summary>
	 /// <returns></returns>
	void Player::displayOcc(vector <Territory*> occVector) {
		size_t territoryListSize = occVector.size();
		cout << territoryListSize<< "t amount\n";
		if (territoryListSize == 0) {
			cout << "no territory for displayOcc\n";
			return;
		}
		for (size_t i = 0; i < territoryListSize; i++)
		{
			std::cout << occVector.at(i)->getName() << "\n";
		}
	}
	// getter setter
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

	std::vector <Territory*>Player:: getplayerOccupied() {
		return playerOccupied;
	}

	ostream& operator<<(ostream& os, const Player& d) {
		os << typeid(d).name() << ", Player info: pid" << d.pid << "playername:" << d.playerName;
		return os;
	}

	PlayerList::PlayerList() {
	};

	PlayerList::PlayerList(const PlayerList&pl) {
		this->list=pl.list;
	}

	void PlayerList::addPlayer(Player p) {
		list.push_back(p);
	};

	Player PlayerList::findPlayer(int i) {
		return list[i];
	};

	Player PlayerList::findPlayerbyName(string name) {
		for (int i = 0; i < list.size(); i++) {
			if (findPlayer(i).getPlayerName() == name) {
				return findPlayer(i);
			}
		}
		cout << "player "<<name<<" not found";
		return Player();
	}