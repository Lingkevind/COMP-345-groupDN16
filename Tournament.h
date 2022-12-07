#ifndef TOURNAMENT_H
#define TOURNAMENT_H
#include "Player.h"
#include "Territory.h"
#include "Coord.h"
#include "MapLoader.h"
//Here defines the Tournament object for storing the data and attribute used in the tournament mode.
class Tournament {
private:
	//map list and player list for storing maps and players
	vector<Map*> mapList;
	vector<Player*> playerList;
	//this player list copy is the list used in game which allows erasing player, will be reset as game reset
	vector<Player*> copyPlayerList;
	int gameCount;
	int turnCount;
public:
	//the nested vecotr that stores the table of game result
	vector<vector<string>> result;
	Tournament();
	Tournament(vector<Map*> m, vector<Player*>p, int g, int d);
	Tournament(const Tournament& t);
	vector<Map*> getMapList();
	Map* getMap(int index);
	vector<Player*> getPlayerList();
	vector<Player*> getCopyPlayerList();
	Player* getPlayer(int index);
	void addMap(Map* m);
	void addPlayer(Player* p);
	void removePlayer(int index);
	void copyPlayer();
	void setGameCount(int count);
	void setTurnCount(int count);
	int getGameCount();
	int getTurnCount();
};
#endif