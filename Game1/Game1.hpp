// Game1.h : Include file for standard system include files,
// or project specific include files.
#ifndef GAME1_HPP
#define GAME1_HPP
#pragma once

#include <iostream>

// TODO: Reference additional headers your program requires here.


struct Garbage{
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	int speed;
	int type;	
};

// function definitions
	void spawnGarbage(vector<Garbage>& TrashCan);
#endif