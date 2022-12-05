#ifndef TOURNAMENT_H
#define TOURNAMENT_H
#include "GameEngine.h"

class Tournament {
private:
	vector<Map*> mapList;
	vector<Player*> playerList;
	vector<Player*> copyPlayerList;
	int gameCount;
	int turnCount;
public:
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