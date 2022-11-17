#include "Player.h"

	/// <summary>
	/// default player
	/// </summary>
	Player::Player()
	{
		std::string playerName = "default";
		ArmyUnit = 0;
		pid = -1;
		playerHand = new Hand();
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
	Player::Player(std::string newName) {
		this->playerName = newName;
		pid+=playerNum;
		ArmyUnit = 0;
		playerHand = new Hand();
		oList = new OrderList();
	}

	/// <param name="copyPlayer">copy constructer</param>
	Player::Player(const Player &copyPlayer)
	{
		this->playerName = copyPlayer.playerName;
		this->pid = playerNum++;
		this->playerOccupied = copyPlayer.playerOccupied;
		this->playerHand = (copyPlayer.playerHand);
		this->oList = copyPlayer.oList; //new
	}
	/// <summary>
	/// player playing the game
	/// </summary>
	/// playerOccupied show Territory occupyed by player
	/// 
	/// playerHand is a pointer point to player's hand
	/// 
	Player::Player(std::string newName, int newPid, std::vector <Territory*> newplayerOccupied, Hand* h)
	{
		playerName = newName;
		pid = newPid;
		playerOccupied = newplayerOccupied;
		playerHand = h;
		Order *playerOrderlist = new Order;
	}

	Player::~Player(){}

	/// <summary>
	/// method toDefend return a list of territories that are to be 
	/// defendedand to be attacked, respectively.
	/// will improve later
	/// </summary>
	/// <returns>a list of Territory that are owned by player</returns>
	vector <Territory*> Player::toDefend()
	{
		//std::vector <Territory>  toDefendVector;
		vector <Territory*> toDefendVector = getFrontierT();
		/*for each (Territory * var in toDefendVectorP)
		{
			toDefendVector.push_back(*var);
		}*/

		return toDefendVector;
	}
	/// <summary>
	/// method toAttack return a list of territories that are to be 
	/// defendedand to be attacked, respectively.
	/// will improve later
	/// </summary>
	/// <returns>a list of Territory player can attack</returns>
	vector <Territory*>Player::toAttack () {
		std::vector <Territory*> toAttackVector  = getFrontierT();
		//std::vector <Territory> toAttackVector;
		/*for each (Territory* var in toAttackVectorP)
		{
			toAttackVector.push_back(*var);
		}*/
		
		//sort(toAttackVector.begin(), toAttackVector.end());
		//toAttackVector.erase(unique(toAttackVector.begin(), toAttackVector.end()));


		return toAttackVector;
	}

	vector<Territory*> Player::getFrontierT()
	{
		std::vector<Territory*> v;
		for each (Territory * t in playerOccupied) {
			std::vector<Territory*> tPla = t->getAdjacentTerritories();
			for each (Territory * t1 in tPla){
				v.insert(v.end(), t1);
			}
		}
		return v;
	}

	/// <summary>
	/// creat a order and add it to player's playerOrderlist
	/// </summary>
	void Player::issueOrder()
	{
		Order newPlayerOrder(1);
		playerOrderlist=(playerOrderlist, newPlayerOrder);
		
	}
	
	void Player::attack(Player pd) {
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
				t->setControllingPlayer(nullptr);
				return;
			} //else { cout << "not find t\n"; }
		}
		cout << "not find "+t->getName() + "in this player's playerOccupied\n";
	}	

	string Player::occupy(Territory* t) {
		this->playerOccupied.push_back(t);
		t->setControllingPlayer(this);
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
	bool Player::isLosttheGame()
	{
		auto a = 0;
		bool lostAllTerritory = false;
		if (true){	//during thegame
			lostAllTerritory = this->getplayerOccupied().size() == a;
		}
		
		return lostAllTerritory;
	}

	//bool Player::ownTerritory(Territory t) {
	//	if (find(playerOccupied.begin(), playerOccupied.end(), t) != playerOccupied.end()) {
	//		return true;
	//	}
	//	else {
	//		return false;
	//	}
	//};

	/// <summary>
	/// displayer player's info 
	/// will be delete later
	/// </summary>
	void Player::displayerOcc() { 
		cout << "Player: " << this->getPlayerName() << " has:\n";
		displayOcc(getplayerOccupied());
	}
	 /// <summary>
	 /// used to display Territory list
	 /// </summary>
	 /// <returns></returns>
	void Player::displayOcc(vector <Territory*> occVector) {
		size_t territoryListSize = occVector.size();
		cout << territoryListSize<< " Territory\n";
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

	void Player::setArmyUnit(int i)
	{
		//int num = i;
		ArmyUnit = i;
	}
	
	std::string Player::getPlayerName() {
		std::string str = "def";
		str = playerName;
		//std::cout << "player name: " << str << "\n";
		return str;
	}

	Hand* Player::getplayerHand()
	{
		return playerHand;
	}

	std::vector <Territory*>Player:: getplayerOccupied() {
		return playerOccupied;
	}

	int Player::getplayerOccupiedsize() {
		return playerOccupied.size();
	}

	ostream& operator<<(ostream& os, const Player& d) {
		os << typeid(d).name() << ", Player info: pid" << d.pid<< "playername:" << d.playerName<<"player order list" << d.playerOrderlist;
		return os;
	}

	/// <summary>
	/// testPlayer
	/// </summary>

	/*PlayerList::PlayerList() {
	};

	PlayerList::PlayerList(vector<Player> pList) {
		this->list = pList;
	};

	PlayerList::PlayerList(const PlayerList& pl) {
		this->list = pl.list;
	}

	void PlayerList::addPlayer(Player p) {
		list.push_back(p);
	};

	Player PlayerList::findPlayer(int i) {
		return list[i];
	};*/

	



	void testPlayer()
	{
		cout << "welcome!\n comp345 assiignment1 v2" << " now creat new player\n\tplease type your name\n";
		string userName;
		cin >> userName;
		string *nameP = &userName;
		Player player("userInput");
		player.setPlayerName(*nameP);
		cout << "hi!\t" << player.getPlayerName() << "  your player ID is:  " << player.pid <<"\n";
		//player.getplayerOccupied();


		vector<Territory> territoriesV;
		vector<Territory>* territoriesVptr;
		territoriesVptr = &territoriesV;
		vector<Territory*> territoriesVptrp;
		vector<Continent*> c1ptr;
		vector<Continent> c1;

		Territory* t1 = new Territory;
		t1->setName("t1");
		territoriesVptrp.push_back(t1);
		Territory* t2 = new Territory;
		t2->setName("t2");
		territoriesVptrp.push_back(t2);
		Territory* t3 = new Territory;
		t3->setName("t3");
		territoriesVptrp.push_back(t3);
		Territory* t4 = new Territory;
		t4->setName("t4");
		territoriesVptrp.push_back(t4);
		Territory* t5 = new Territory;
		t5->setName("t5");
		territoriesVptrp.push_back(t5);
		Territory* t6 = new Territory;
		t6->setName("t6");
		territoriesVptrp.push_back(t6);
		Territory* t7 = new Territory;
		t7->setName("t7");
		territoriesVptrp.push_back(t7);
		//Player player("userInput");
		Player player2("player2");
		Player player3("player3");
		cout << player.occupy(t1);
		cout << player.occupy(t2);
		cout << player.occupy(t3);
		cout << player2.occupy(t4);
		cout << player2.occupy(t5);
		cout << player3.occupy(t6);
		cout << player3.occupy(t7);
		player.displayerOcc();
		player2.displayerOcc();
		player3.displayerOcc();

		t1->addAjacentTerritory(t2);
		t1->addAjacentTerritory(t3);
		t2->addAjacentTerritory(t1);
		t2->addAjacentTerritory(t3);
		t2->addAjacentTerritory(t4);
		t3->addAjacentTerritory(t1);
		t3->addAjacentTerritory(t6);
		t4->addAjacentTerritory(t2);
		t4->addAjacentTerritory(t5);
		t5->addAjacentTerritory(t4);
		t5->addAjacentTerritory(t7);
		t6->addAjacentTerritory(t3);
		t6->addAjacentTerritory(t5);

		player.displayOcc(territoriesVptrp);
		cout << "\ngetAdjacentTerritories\n";
		vector<Territory*> tAdj1 = t2->getAdjacentTerritories();
		player.displayOcc(tAdj1);

		cout << "\ngetFrontierT\n";
		vector<Territory*> v = player.getFrontierT();
		player.displayOcc(v);
		player.displayerOcc();
		vector<Territory*> vToAttack = player.toAttack();
		vector<Territory*> vToDefend = player.toDefend();
		cout << "\nplayer.toAttack()" << "\n";
		player.displayOcc(vToAttack);
		cout << "\nplayer.toDefend()" << "\n";
		player.displayOcc(vToDefend);
		
		//cout << "getAdjacentTerritories\n";
		//player.displayOcc(player.toAttack());
		//player.displayOcc(player.toDefend());
		//player.issueOrder();
		//player.issueOrder();
		//player.issueOrder();
	}