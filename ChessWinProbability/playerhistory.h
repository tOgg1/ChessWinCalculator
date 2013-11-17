#pragma once
#include "player.h"
#include "match.h"
#include <vector>

class Player;
class Match;

enum PlayerNum
{
	PLAYERONE = 0,
	PLAYERTWO = 1
};

struct ResultDistr
{
	float playerOneProb;
	float playerTwoProb;
	float drawProb;
};

class PlayerHistory
{
public:
	PlayerHistory(Player& one, Player& two);
	~PlayerHistory(void);

	void addMatch(Match& match);
	void removeMatch(Match& match);

	ResultDistr resultDistributionFromHistory();
	ResultDistr resultDistributionFromELO(bool useHistoryRatio, float decisiveDrawRatio);

	bool playerIsPartOf(Player& player);

private:
	Player* players;
	std::vector<Match> matches;

	int countP1Win;
	int countP2Win;
	int countDraw;
	int matchCount;

	void redoCalculations();
};

