#include "player.h"

Player::Player(char* name, int elo, int playerid)
{
	this->name = name;
	this->playerid = playerid;
	this->elo = elo;
}

Player::~Player(void)
{

}

char* Player::getName()
{
	return this->name;
}

int Player::getElo()
{
	return this->elo;
}

void Player::addPlayerHistory(PlayerHistory history)
{
	this->histories.push_back(history);
}

PlayerHistory& Player::getPlayerHistory(Player& other)
{
	std::vector<PlayerHistory>::iterator it;

	for(it = histories.begin(); it != histories.end(); ++it)
	{
		if(it->playerIsPartOf(other))
			return *it;
	}
}
