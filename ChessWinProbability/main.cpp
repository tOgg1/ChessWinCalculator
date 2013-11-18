#define _CRT_SECURE_NO_WARNINGS

#include "player.h"
#include "playerhistory.h"
#include "match.h"
#include "probcalc.h"
#include "stdio.h"
#include <vector>

Player* carlsen;
Player* anand;
PlayerHistory* history;
PlayerHistory* recentHistory;

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
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Chess classic Mainz Anand-win
	history->addMatch(Match(*carlsen, *anand, Result(BLACK), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(WHITE), ++id));

	//Morelia-Linares draw
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Linares draw
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Linares Carlsen-win
	history->addMatch(Match(*carlsen, *anand, Result(WHITE), ++id));

	//Tal Memorial draw
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	// London Chess Classic 2010 draw
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Bilbao Masters 2010 draw
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Bilbao Masters 2010 Anand-win
	history->addMatch(Match(*carlsen, *anand, Result(BLACK), ++id));

	//Nanjing Pearl Spring Tournament 2010 draw
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Arctic Securities Chess Stars 2010
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));
	history->addMatch(Match(*carlsen, *anand, Result(WHITE), ++id));

	//Corus
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//London Chess Classic 2011
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Tata Steel
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	//Tal Memorial 2011
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Bilbao Masters 2011
	history->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	history->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

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

	recentHistory = new PlayerHistory(*carlsen, *anand);

	//London Chess Classic 2011
	recentHistory->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Tata Steel
	recentHistory->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	//Tal Memorial 2011
	recentHistory->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//Bilbao Masters 2011
	recentHistory->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	recentHistory->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	//London Chess classic draw
	recentHistory->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	// Tata steel draw
	recentHistory->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	//London Chess classic draw
	recentHistory->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	// Bilbao masters draw
	recentHistory->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	// Bilbao masters Carlsen-win
	recentHistory->addMatch(Match(*carlsen, *anand, Result(WHITE), ++id));

	//Tata steel draw
	recentHistory->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

	// Tal memorial Carlsen-win
	recentHistory->addMatch(Match(*carlsen, *anand, Result(WHITE), ++id));

	// Norway Chess draw
	recentHistory->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));

	// WC (so far)
	recentHistory->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	recentHistory->addMatch(Match(*carlsen, *anand, Result(DRAW), ++id));
	recentHistory->addMatch(Match(*carlsen, *anand, Result(WHITE), ++id));

	recentHistory->addMatch(Match(*anand, *carlsen, Result(BLACK), ++id));
	recentHistory->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));
	recentHistory->addMatch(Match(*anand, *carlsen, Result(BLACK), ++id));
	recentHistory->addMatch(Match(*anand, *carlsen, Result(DRAW), ++id));

}

int main(int argc, char** argv)
{
	setupCarlsenAnand();

	FILE* file = fopen("results.txt", "a");
	fprintf(file, "\n");
	fprintf(file, "\n");

	ProbCalc calc;
	
	float drawProb;
	ResultDistr histRes = history->resultDistributionFromHistory();
	float drawHistoryProb = histRes.drawProb;
	bool useDrawHistory = false;
	int historyEmphasis, eloEmphasis;
	std::vector<ResultDistr> results;
	std::vector<ResultDistr> eloResults;

	for(int i = 40; i <= 80; ++i)
	{
		fprintf(file, "\n");
		drawProb = (float)i/100.0f;
		for (int j = 0; j <= 10; j++)
		{
			historyEmphasis = j;
			eloEmphasis = 10-j;

			ResultDistr match = calc.calculateMatchProbablity(*history, 7, 6.5, 4.5, 2.5, 1, useDrawHistory, drawProb, true, true, historyEmphasis, eloEmphasis);
			results.push_back(match);
			fprintf(file, "\n%f \t%s \t%i \t%i \t%f \t%f \t%f", drawProb, useDrawHistory == true ? "true" : "false", historyEmphasis, eloEmphasis, match.playerTwoProb*100, match.playerOneProb*100, match.drawProb*100);
			if(eloEmphasis == 10)
			{
				eloResults.push_back(match);
			}
		}			
	}

	fprintf(file, "\n");

	useDrawHistory = true;
	for(int j = 0; j <= 10; j++)
	{
		historyEmphasis = j;
		eloEmphasis = 10-j;
		ResultDistr match = calc.calculateMatchProbablity(*history, 7, 6.5, 4.5, 2.5, 1, useDrawHistory, drawHistoryProb, true, true, historyEmphasis, eloEmphasis);
		results.push_back(match);
		fprintf(file, "\n%f \t%s \t%i \t%i \t%f \t%f \t%f", drawHistoryProb, useDrawHistory == true ? "true" : "false", historyEmphasis, eloEmphasis, match.playerTwoProb*100, match.playerOneProb*100, match.drawProb*100);
		if(eloEmphasis == 10)
		{
			eloResults.push_back(match);
		}
	}
		
	std::vector<ResultDistr>::iterator it;

	int length = results.size();
	float accumulation = 0;

	for(it = results.begin(); it != results.end(); ++it)
	{
		accumulation += it->playerOneProb;
	}

	float mean = accumulation/(float)length;

	accumulation = 0;
	for(it = results.begin(); it != results.end(); ++it)
	{
		accumulation = pow((it->playerOneProb - mean), 2);
	}

	float sd = sqrt((1/((float)(length-1)))*accumulation);
	fprintf(file, "\nResults of measurements:\nProbability that Carlsen wins: %f +-%f", mean*100,sd*100);


	accumulation = 0;
	length = eloResults.size();

	for(it = eloResults.begin(); it != eloResults.end(); ++it)
	{
		accumulation += it->playerOneProb;
	}

	mean = accumulation/(float)length;

	accumulation = 0;
	for(it = eloResults.begin(); it != eloResults.end(); ++it)
	{
		accumulation = pow((it->playerOneProb - mean), 2);
	}

	sd = sqrt((1/((float)(length-1)))*accumulation);
	fprintf(file, "\nResults of measurements from ELO:\nProbability that Carlsen wins: %f +-%f", mean*100,sd*100);

	return 0;
}