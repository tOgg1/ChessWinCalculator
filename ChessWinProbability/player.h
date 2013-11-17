#pragma once
#include <string>
#include <vector>
#include "playerhistory.h"
#include <string>

class PlayerHistory;

enum PlayerSide
{
	PLAYERWHITE,
	PLAYERBLACK
};

class Player
{
public:
	Player(void){};
	Player(char* name, int elo, int playerid);
	~Player(void);

	void addPlayerHistory(PlayerHistory history);
	PlayerHistory& getPlayerHistory(Player& other);

	char* getName();
	int getElo();
	bool operator ==(Player& other){return other.playerid == playerid;};

private:
	int playerid;
	char* name;
	float elo;
	std::vector<PlayerHistory> histories;

};

