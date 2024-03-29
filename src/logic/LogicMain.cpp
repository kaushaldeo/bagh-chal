/**
* Test program
*
* IMPORTANT: This is all commented out due to compiling error without Qt Creator
*
*/

/*
#include "PlayerTiger.h"
#include "Game.h"
#include "Grid.h"
#include "Cell.h"
#include "FileIO.h"
#include <iostream>

using namespace std;

void printGrid(Game *game)
{
	cout << "Printing entire Grid:\n";

	for(int y = 0; y < 5; ++y)
	{
		for(int x = 0; x < 5; ++x)
		{
			cout << game->getGrid().getCell(x, y)->getStatus() << " ";
		}

		cout << "\n";
	}
}

int main()
{
	Game *myGame = Game::getInstance();

	cout << "TESTCASE 1: beginning conditions\n\n";

	Tiger **allTigers = myGame->getTiger().getTigers();

	cout << "Tigers should now reside on (0,0), (0,4), (4,0) and (4,4)\n";

	for (int i = 0; i < 4; ++i)
	{
		cout << "Tiger " << i << " resides on " << (allTigers[i]->getCell()->getPosition()).first << "," << (allTigers[i]->getCell()->getPosition()).second << "\n";
	}

	printGrid(myGame);
        
	cout << "\nTESTCASE 2: setting goats\n\n";

	Cell *case2EmptyCell = myGame->getGrid().getCell(1, 1);
	Cell *case2TigerCell = myGame->getGrid().getCell(0, 0);

	cout << "Trying to set Goat on Cell 1, 1 with Status " << case2EmptyCell->getStatus() << " (should be 0)\n";
	cout << "Returned " << myGame->getGoat().canMoveThere(NULL, case2EmptyCell) << "(should be 1)\n";
	myGame->getGoat().move(NULL, case2EmptyCell);

	cout << "Trying to set Goat on Cell 0, 0 with Status " << case2TigerCell->getStatus() << " (should be 1)\n";
	cout << "Returned " << myGame->getGoat().canMoveThere(NULL, case2TigerCell) << "(should be 0)\n";
	
	try
	{
		myGame->getGoat().move(NULL, case2TigerCell);
		cout << "Placed goat on occupied cell\nFAIL!!!!";
		return -1;
	}
	catch (CanNotMoveException* e)
	{
		cout << "Caught CanNotMoveException.\n";
	}

	printGrid(myGame);
    
    cout << "File I/O Test: Saving game:" << endl;
	FileIO io ("/home/htwg/Dokumente/test.txt");
	io.saveGame();
	cout << "Game saved." << endl;
         
	cout << "\nTESTCASE 3: moving tigers\n\n";		

	Cell *case3_4_0 = myGame->getGrid().getCell(4, 0);
	Cell *case3EmptyNeighborOf_4_0 = myGame->getGrid().getCell(3, 0);

	Cell *case3_0_0 = myGame->getGrid().getCell(0, 0);
	Cell *case3GoatNeighborOf_0_0 = myGame->getGrid().getCell(1, 1);
	Cell *case3GoatGetsEatenNeighborOf_0_0 = myGame->getGrid().getCell(2, 2);

	Cell *case3_4_4 = myGame->getGrid().getCell(4, 4);
	Cell *case3NotNeighborOf_4_4 = myGame->getGrid().getCell(3, 0);

	cout << "Trying to move Tiger from 4, 0 to 3, 0 with Status " << case3EmptyNeighborOf_4_0->getStatus() << " (should be 0)\n";
	cout << "Returned " << myGame->getTiger().canMoveThere(case3_4_0, case3EmptyNeighborOf_4_0) << " (should be 1)\n";
	try
	{
		myGame->getTiger().move(case3_4_0, case3EmptyNeighborOf_4_0);
		cout << "Expected MustEatException!\nFAIL!!!";
	}
	catch (MustEatException* e)
	{
		cout << "MustEatException gefangen.\n";
	}

	cout << "Trying to move Tiger from 0, 0 to 1, 1 with Status " << case3GoatNeighborOf_0_0->getStatus() << " (should be 2)\n";
	cout << "Returned " << myGame->getTiger().canMoveThere(case3_0_0, case3GoatNeighborOf_0_0) << " (should be 0)\n";

	try
	{
		cout << "Trying to move Tiger from 0, 0 to 2, 2 with Status " << case3GoatGetsEatenNeighborOf_0_0->getStatus() << " (should be 0)\n";
		cout << "Returned " << myGame->getTiger().canMoveThere(case3_0_0, case3GoatGetsEatenNeighborOf_0_0) << " (should be 1)\n";
		myGame->getTiger().move(case3_0_0, case3GoatGetsEatenNeighborOf_0_0);
	}
	catch (TigerEatGoatException* e)
	{
		cout << "Ziege gefressen" << endl;
	}

	printGrid(myGame);
    
    cout << "File I/O Test: Loading game" << endl;
	io.loadGame();
	cout << "Game loaded.";
	printGrid(myGame);
        
    cout << "\nTESTCASE 3: Tiger Jumps over Tiger\n\n";        
	Game::startNewGame();
	myGame = Game::getInstance();
	myGame->getTiger().getTigers()[3]->getCell()->removeTiger();
	myGame->getTiger().getTigers()[3]->getCell()->setStatus(empty);
	myGame->getTiger().getTigers()[3]->setCell(myGame->getGrid().getCell(1,1));
	myGame->getGrid().getCell(1,1)->setTiger(myGame->getTiger().getTigers()[3]);
	myGame->getGrid().getCell(1,1)->setStatus(tiger);
	printGrid(myGame);
	
	try 
	{
		myGame->getTiger().move(myGame->getGrid().getCell(0,0), myGame->getGrid().getCell(2,2));
		cout << "No exception has occured!\nFAIL!!!";
		return -1;
	}
	catch (CanNotMoveException *e)
	{
		cout << "CanNotMoveException gefangen.\n";
	}
	
	printGrid(myGame);        
}
*/