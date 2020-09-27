//
// Main.cpp
//
// Created by Eddie Mestre on 9/12/2020
// Copright © 2020 Eddie Mestre. All rights reserved.
//

#include "GameEngine.h"
#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{

	// Create instance of game
	Game game;

	// if Initialize returns true, run loop
	if (game.Initialize() == true) {
		game.RunLoop();
		game.Shutdown();
	}

	return 0;
}