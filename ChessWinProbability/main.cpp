#define _CRT_SECURE_NO_WARNINGS

#include "player.h"
#include "playerhistory.h"
#include "match.h"
#include "probcalc.h"
#include "stdio.h"

Player* carlsen;
Player* anand;
PlayerHistory* history;

// Chessgames found from http://www.chessgames.com/perl/chess.pl?page=1&player=Carlsen&player2=Anand&playercomp=either&eresult=
void setupCarlsenAnand()
{
	int id = 0;
	carlsen = new Player("Magnus Carlsen", 2870, 1);
	anand = new Player("Viswanathan Anand", 2775, 2);

	history = new PlayerHistory(*carlsen, *anand);

	//Ciudad de Leon draw
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	
	//Ciudad de Leon Anand-win
	history->addMatch(Match(*anand, *carlsen, Result(WHITE), ++id));

	//Ciudad de Leon draw
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	//Ciudad de Leon Anand-win
	history->addMatch(Match(*anand, *carlsen, Result(WHITE), ++id));

	// Dortmund draw
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	// Linares-Morelia
	history->addMatch(Match(*anand, *carlsen, Result(WHITE), ++id));

	// Linares-Morelia Anand-win
	history->addMatch(Match(*anand, *carlsen, Result(WHITE), ++id));

	// Linares-Morelia Anand-win
	history->addMatch(Match(*carlsen, *anand, Result(BLACK), ++id));

	// Corus draw
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	// Morelia-Linares draw
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));
	
	// Morelia-Linares Anand-win
	history->addMatch(Match(*carlsen, *anand, Result(BLACK), ++id));

	// Corus Anand-win
	history->addMatch(Match(*carlsen, *anand, Result(BLACK), ++id));

	// Bilbao Grand slam draws
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Chess Classic Mainz Draws
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Chess classic Mainz Anand-wins
	history->addMatch(Match(*carlsen, *anand, Result(WHITE), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(BLACK), ++id));

	//London Chess classic draw
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	// Tata steel draw
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	//London Chess classic draw
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	// Bilbao masters draw
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	// Bilbao masters Carlsen-win
	history->addMatch(Match(*carlsen, *anand, Result(WHITE), ++id));

	//Tata steel draw
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	// Tal memorial Carlsen-win
	history->addMatch(Match(*carlsen, *anand, Result(WHITE), ++id));

	// Norway Chess draw
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	// WC (so far)
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	history->addMatch(Match(*carlsen, *anand, Result(WHITE), ++id));

	history->addMatch(Match(*anand, *carlsen, Result(BLACK), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(BLACK), ++id));

}

int main(int argc, char** argv)
{
	setupCarlsenAnand();

	FILE* file = fopen("results.txt", "a");

	ProbCalc calc;
	
	float drawProb;
	ResultDistr histRes = history->resultDistributionFromHistory();
	float drawHistoryProb = histRes.drawProb;
	bool useDrawHistory = false;
	int historyEmphasis, eloEmphasis;

	for(int i = 40; i <= 80; ++i)
	{
		fprintf(file, "\n");
		drawProb = (float)i/100.0f;
		for (int j = 0; j <= 10; j++)
		{
			historyEmphasis = j;
			eloEmphasis = 10-j;

			ResultDistr match = calc.calculateMatchProbablity(*history, 6, 6.5, 4, 2, 1, useDrawHistory, drawProb, true, true, historyEmphasis, eloEmphasis);
			fprintf(file, "\n%f \t%s \t%i \t%i \t%f \t%f \t%f", drawProb, useDrawHistory == true ? "true" : "false", historyEmphasis, eloEmphasis, match.playerTwoProb, match.playerOneProb, match.drawProb);
		}			
	}

	useDrawHistory = true;
	for(int j = 0; j <= 10; j++)
	{
		historyEmphasis = j;
		eloEmphasis = 10-j;
		ResultDistr match = calc.calculateMatchProbablity(*history, 6, 6.5, 4, 2, 1, useDrawHistory, drawHistoryProb, true, true, historyEmphasis, eloEmphasis);
		fprintf(file, "\n%f \t%s \t%i \t%i \t%f \t%f \t%f", drawHistoryProb, useDrawHistory == true ? "true" : "false", historyEmphasis, eloEmphasis, match.playerTwoProb, match.playerOneProb, match.drawProb);
	}
		
	return 0;
}