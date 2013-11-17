#include "match.h"

Match::Match(Player& one, Player& two, Result result, int id)
{
	this->players = new Player[2];
	this->id = id;
	this->players[0] = one;
	this->players[1] = two;
	this->result = result;
}

Match::~Match(void)
{
	
}

float Match::getPointsForPlayer(PlayerSide player)
{
	return 0.0f;
}

int Match::getSystemPointsForPlayer(Player& player)
{
	if(result == DRAW)
		return 0;
	
	if(players[0] == player)
	{
		return result;
	}
	else if(players[1] == player)
	{
		return -result;
	}
	return -2;
}


float Match::getPointsForPlayer(Player& player)
{
	if(result == DRAW)
		return 0.5;

	if(players[0] == player)
	{
		if(result == WHITE)
			return 1;
		else if(result == BLACK)
			return 0;
	}
	else if(players[1] == player)
	{
		if(result == WHITE)
			return 0;
		else if(result == BLACK)
			return 1;
	}
	return -2;
}

Player* Match::getPlayers()
{
	return players;
}




