#pragma once
#include "player.h"
#include "playerhistory.h"
#include "match.h"

class ProbCalc
{
public:
	ProbCalc(void);
	~ProbCalc(void);

	ResultDistr calculateMatchProbablity(PlayerHistory hist, int gamesplayed, float pointRoof, float playerOnePoints, float playerTwoPoints, float psychologicalRatio, bool useDrawHistory, float drawProbDefault, bool useHistory,  bool useElo, int historyEmphasis, int eloEmphasis);

private:
	float calculateInternalProbablityForLosingPlayer(int gamesleft, int pointsbehind, float probWin, float probDraw, float probLose);
	float calculateInternalProbabilityForDraw(int gamesleft, int pointsbehind, float probWin, float probDraw, float probLose);
};

