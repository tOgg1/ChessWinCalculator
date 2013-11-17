#include "playerhistory.h"
#include "stdio.h"


PlayerHistory::PlayerHistory(Player& one, Player& two)
{
	players = new Player[2];
	players[0] = one;
	players[1] = two;
	this->countDraw  = 0;
	this->countP1Win = 0;
	this->countP2Win = 0;
}


PlayerHistory::~PlayerHistory(void)
{

}

void PlayerHistory::addMatch(Match& match)
{
	this->matches.push_back(match);
	this->redoCalculations();
}

void PlayerHistory::removeMatch(Match& match)
{
	std::vector<Match>::iterator i = std::find(matches.begin(), matches.end(), match);
	if(i == matches.end())
		return;
	this->matches.erase(i);
	this->redoCalculations();
}


ResultDistr PlayerHistory::resultDistributionFromHistory()
{
	ResultDistr distr;

	distr.drawProb = this->countDraw/(float)this->matchCount;
	distr.playerOneProb = this->countP1Win/(float)this->matchCount;
	distr.playerTwoProb = this->countP2Win/(float)this->matchCount;

	return distr;
}

// The draw ratio is the amount of games(in percent) that are assumed to be drawn. If no such value is passed in,
// (and the useHistoryRatio-flag is set) the value is calculated based on the historicity of the players.
// If no value is passed and history is not used, the ratio is assumed to be 50/50.
// For mathematical details, see http://en.wikipedia.org/wiki/Elo_rating_system#Theory
ResultDistr PlayerHistory::resultDistributionFromELO(bool useHistoryRatio, float drawRatio)
{
	float Qa = pow(10, (float)players[0].getElo()/(float)400);
	float Qb = pow(10, (float)players[1].getElo()/(float)400);

	float Ea = (Qa)/(Qa + Qb);
	float Eb = (Qb)/(Qa + Qb);

	if(!useHistoryRatio)
	{
		if(!(drawRatio >= 0 && drawRatio <= 1))
		{
			drawRatio = 0.5;
		}
	}
	else
	{
		drawRatio = (float)this->countDraw/(float)this->matchCount;
	}

	float p1win = (1 - drawRatio)*Ea;
	float p2win = (1 - drawRatio)*Eb;
	
	ResultDistr distr;
	distr.drawProb = drawRatio;
	distr.playerOneProb = p1win;
	distr.playerTwoProb = p2win;
	return distr;
}

void PlayerHistory::redoCalculations()
{
	this->matchCount = matches.size();
	std::vector<Match>::iterator it;
	this->countDraw = 0;
	this->countP1Win = 0;
	this->countP2Win = 0;
	
	for(it = matches.begin(); it != matches.end(); ++it)
	{
		int res = it->getSystemPointsForPlayer(players[0]);

		if(res == 0)
			++this->countDraw;
		else if(res == 1)
			++this->countP1Win;
		else if(res == -1)
			++this->countP2Win;
	}
}

bool PlayerHistory::playerIsPartOf(Player& player)
{
	return players[0] == player || players[1] == player;
}



