#include "probcalc.h"
#include "playerhistory.h"

#define EPSILON 1e-3

ProbCalc::ProbCalc(void)
{

}

ProbCalc::~ProbCalc(void)
{

}

inline bool assertFloat(float one, float two)
{
	return abs(one-two) < EPSILON;
}

inline int factorial(int x) {
	return (x == 1 || x < 1) ? 1 : x * factorial(x - 1);
}

ResultDistr ProbCalc::calculateMatchProbablity(PlayerHistory hist, int gamesplayed, float pointRoof, float playerOnePoints, float playerTwoPoints, float psychologicalRatio, bool useDrawHistory, float drawProbDefault, bool useHistory,  bool useElo, int historyEmphasis, int eloEmphasis)
{
	ResultDistr matchDistr;

	matchDistr.drawProb = 0.0;
	matchDistr.playerOneProb = 0.0;
	matchDistr.playerTwoProb = 0.0;
	
	if(playerOnePoints + playerTwoPoints != gamesplayed)
	{
		printf("Something is off with your math dude");
		return matchDistr;
	}

	bool oneIsLeading = playerOnePoints >= playerTwoPoints;


	// The games left
	int gamesleft = (pointRoof-0.5f) * 2 - gamesplayed; 
	int totalgames = gamesplayed + gamesleft;

	// This number is equal to the amount of games the losing player has to win to win
	int pointsbehind = abs(playerOnePoints - playerTwoPoints) + 1;

	if(pointsbehind > gamesleft)
	{
		if(oneIsLeading)
		{
			matchDistr.drawProb = 0;
			matchDistr.playerOneProb = 1.0;
			matchDistr.playerTwoProb = 0.0;
		}
		else
		{
			matchDistr.drawProb = 0;
			matchDistr.playerOneProb = 0.0;
			matchDistr.playerTwoProb = 1.0;
		}
		return matchDistr;
	}

	if(!useHistory && !useElo)
	{
		printf("You kind of have to use something...");
		return matchDistr;
	}

	ResultDistr historyDistr = hist.resultDistributionFromHistory();
	ResultDistr eloDistr;
	if(useDrawHistory)
	{
		eloDistr = hist.resultDistributionFromELO(true, 0);
	}
	else
	{
		eloDistr = hist.resultDistributionFromELO(false, drawProbDefault);
	}

	float Qhist = (float)historyEmphasis/(float)(historyEmphasis + eloEmphasis);
	float Qelo = (float)eloEmphasis/(float)(historyEmphasis + eloEmphasis);

	ResultDistr finalDistr;
	if(useElo && useHistory)
	{
		finalDistr.drawProb = Qhist*historyDistr.drawProb + Qelo*eloDistr.drawProb;
		finalDistr.playerOneProb = Qhist*historyDistr.playerOneProb + Qelo*eloDistr.playerOneProb;
		finalDistr.playerTwoProb = Qhist*historyDistr.playerTwoProb + Qelo*eloDistr.playerTwoProb;
	}
	else if(useElo)
	{
		finalDistr.drawProb = eloDistr.drawProb;
		finalDistr.playerOneProb = eloDistr.playerOneProb;
		finalDistr.playerTwoProb = eloDistr.playerTwoProb;
	}
	else
	{
		finalDistr.drawProb = historyDistr.drawProb;
		finalDistr.playerOneProb = historyDistr.playerOneProb;
		finalDistr.playerTwoProb = historyDistr.playerTwoProb;
	}


	float losingProb, drawProb, winningProb;

	if(oneIsLeading)
	{
		losingProb = calculateInternalProbablityForLosingPlayer(gamesleft, pointsbehind, finalDistr.playerTwoProb, finalDistr.drawProb, finalDistr.playerOneProb);
		drawProb = calculateInternalProbabilityForDraw(gamesleft, pointsbehind, finalDistr.playerTwoProb, finalDistr.drawProb, finalDistr.playerOneProb);
		winningProb = 1 - losingProb - drawProb;

		matchDistr.playerOneProb = winningProb;
		matchDistr.playerTwoProb = losingProb;
		matchDistr.drawProb = drawProb;
	}
	else
	{
		losingProb = calculateInternalProbablityForLosingPlayer(gamesleft, pointsbehind, finalDistr.playerOneProb, finalDistr.drawProb, finalDistr.playerTwoProb);
		drawProb = calculateInternalProbabilityForDraw(gamesleft, pointsbehind, finalDistr.playerOneProb, finalDistr.drawProb, finalDistr.playerTwoProb);
		winningProb = 1 - losingProb - drawProb;

		matchDistr.playerOneProb = losingProb;
		matchDistr.playerTwoProb = winningProb;
		matchDistr.drawProb = drawProb;
	}	
	return matchDistr;
}

float ProbCalc::calculateInternalProbablityForLosingPlayer(int gamesleft, int pointsbehind, float probWin, float probDraw, float probLose)
{
	float total = 0;
	for (int i = pointsbehind; i <= gamesleft; i++)
	{ 
		float winChance = 0;
		int fact = factorial(gamesleft);
		//Calculate for i wins and totalgames-i draws
		winChance = (factorial(gamesleft)/(factorial(i)*factorial(gamesleft-i)))*pow(probWin, i)*pow(probDraw, gamesleft-i);

		float tempChance = 0;
		//Calculate for [1 - i-dPoints] wins by opponent (which can occur and still not cause a forced lose)
		for (int j = 1; j <= i - pointsbehind && j + i <= gamesleft; j++)
		{
			tempChance += (factorial(gamesleft)/(factorial(i)*factorial(j)*factorial(gamesleft-i-j)))*pow(probWin,i)*pow(probLose,j)*pow(probDraw, gamesleft-i-j);
		}	
		winChance += tempChance;
		total += winChance;
	}
	return total;
}

float ProbCalc::calculateInternalProbabilityForDraw(int gamesleft, int pointsbehind, float probWin, float probDraw, float probLose)
{
	float total = 0;

	for (int i = pointsbehind-1; i < gamesleft-pointsbehind+1; i++)
	{ 
		float winChance = 0;
		int otherWinCount = i - pointsbehind+1;

		//Calculate for i wins, i-pointsbehind loses, and gamesleft-i-otherwinCount draws
		winChance = (factorial(gamesleft)/(factorial(i)*factorial(gamesleft-i)))*pow(probWin, i)*pow(probDraw, gamesleft-i-otherWinCount)*pow(probLose, otherWinCount);
		total += winChance;
	}
	return total;
}
