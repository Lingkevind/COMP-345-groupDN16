#include "Tournament.h"
using namespace std;

Tournament::Tournament() {
	mapList = vector<Map*>();
	playerList = vector<Player*>();
	gameCount = 0;
	turnCount = 0;
}


Tournament::Tournament(vector<Map*> m, vector<Player*>p, int g, int d) {
	mapList = m;
	playerList = p;
	gameCount = g;
	turnCount = d;
}

Tournament::Tournament(const Tournament& t) {
	mapList = t.mapList;
	playerList = t.playerList;
	gameCount = t.gameCount;
	turnCount = t.turnCount;
}

vector<Map*> Tournament::getMapList() {
	return mapList;
}

Map* Tournament::getMap(int index) {
	return getMapList()[index];
}

vector<Player*> Tournament::getPlayerList() {
	return playerList;
}

vector<Player*> Tournament::getCopyPlayerList() {
	return copyPlayerList;
}

Player* Tournament::getPlayer(int index) {
	return getCopyPlayerList()[index];
}

void Tournament::addMap(Map* m) {
	mapList.push_back(m);
}

void Tournament::addPlayer(Player* p) {
	playerList.push_back(p);
}

void Tournament::removePlayer(int index) {
	delete copyPlayerList[index];
}

void Tournament::copyPlayer() {
	copyPlayerList = playerList;
}

void Tournament::setGameCount(int count) {
	gameCount = count;
}

void Tournament::setTurnCount(int count) {
	turnCount = count;
}

int Tournament::getGameCount() {
	return gameCount;
}

int Tournament::getTurnCount() {
	return turnCount;
}