#pragma once

#include "player.h"

class Player;
enum PlayerSide;

enum Result
{
	BLACK = -1,
	DRAW = 0,
	WHITE = 1
};

class Match
{
public:
	Match(Player& white, Player& black, Result result, int id);
	~Match(void);

	float getPointsForPlayer(PlayerSide player);
	float getPointsForPlayer(Player& player);
	int getSystemPointsForPlayer(Player& player);

	int getResult(Player& player);
	Player* getPlayers();

	bool operator == (Match other){return other.id == id;};

private:
	Player *players;
	Result result;

	int id;
};

