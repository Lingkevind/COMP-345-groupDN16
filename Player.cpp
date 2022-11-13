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
	Player::Player(std::string newName) 
	{
		playerName = newName;
		pid = playerNum++;
	
	}

	/// <param name="copyPlayer">copy constructer</param>
	Player::Player(const Player &copyPlayer)
	{
		playerName = copyPlayer.playerName;
		pid = playerNum++;
		playerOccupied = copyPlayer.playerOccupied;
		*playerHand = *(copyPlayer.playerHand);
	}
	/// <summary>
	/// player playing the game
	/// </summary>
	/// playerOccupied show Territory occupyed by player
	/// 
	/// playerHand is a pointer point to player's hand
	/// 
	Player::Player(std::string newName, int newPid, std::vector <Territory*> newplayerOccupied, Hand h)
	{
		playerName = newName;
		pid = newPid;
		playerOccupied = newplayerOccupied;
		*playerHand = h;
		Order *playerOrderlist = new Order;
	}
	
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
		playerOrderlist=(playerOrderlist, newPlayerOrder);
		
	}
	

	void Player::attack(Player pd)
	{
	std::cout << playerName << "\tattack\t" << pd.playerName <<"\n";
	}
	
	void Player::occupy(Territory* t) 
	{
		this->playerOccupied.push_back(t);
		std::cout << playerName << " occupyed " << t->getName() << "!\n";
	}
	
	//void Player::occupy(Player p) 
	//
	//{
	//	int occNum = p.playerOccupied.size();
	//	for (size_t i = 0; i <occNum; i++)
	//	{
	//		Territory t = p.playerOccupied[i];
	//		playerOccupied.push_back(t);
	//	}
	//	//p.playerOccupied.swap(playerOccupied);
	//}
	/// <summary>
	/// displayer player's info 
	/// will be delete later
	/// </summary>

	//void Player::displayerOcc() {
	//	//int playerSize = playerOccupied.size();<< playerplSize
	//	std::cout << "Player " << getPlayerName() << " territory incoulding: \n";
	//	displayOcc(playerOccupied);
	//}
	 /// <summary>
	 /// used to display Territory list
	 /// </summary>
	 /// <returns></returns>
	// void Player::displayOcc(vector <Continent*> occVector) {
	//	//vector <Territory> newplayerOccupied to cout string
	//	//int occSize = occVector.size();
	//	for (size_t i = 0; i < occVector.size(); i++)
	//	{
	//		string tName = "name blank";
	//		std::cout << tName << "\n";
	//	}
	//}
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
		os << typeid(d).name() << ", Player info: pid" << d.pid<< "playername:" << d.playerName<<"player order list" << d.playerOrderlist;
		return os;
	}


	/// <summary>
	/// testPlayer
	/// </summary>

	void testPlayer()
	{
		cout << "welcome!\n comp345 assiignment1 v2" << " now creat new player\n\tplease type your name\n";
		string userName;
		cin >> userName;
		string *nameP = &userName;
		Player player("userInput");
		player.setPlayerName(*nameP);
		cout << "hi!\t" << player.getPlayerName() << "  your player ID is:  " << player.pid;
		player.getplayerOccupied();
		//cout << "\nplayer.toAttack()" << "\n";

		//player.displayOcc(player.toAttack());
		//cout << "\nplayer.toDefend()" << "\n";
		//player.displayOcc(player.toDefend());
		player.issueOrder();
		player.issueOrder();
		player.issueOrder();
	}