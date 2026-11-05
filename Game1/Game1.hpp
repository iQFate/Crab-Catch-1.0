// Game1.h : Include file for standard system include files,
// or project specific include files.
#ifndef GAME1_HPP
#define GAME1_HPP
#pragma once
#include <raylib.h>

#include <iostream>

// TODO: Reference additional headers your program requires here.

// Garbage class for creating and spawning objects in world
struct Shrimp {
	int posX;
	int posY;
	int speed = 11;
	int sizeX;
	int sizeY;
	Texture2D texture;
};

class Garbage{

	public:
	Garbage(const Texture2D&, const Texture2D&, const Texture2D&);
	void update();
	void draw();
	Rectangle getCollisionRect() const;
	int getType() const;
	int getPosY() const;
	int getPosX() const;


	private:
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	int speed;
	int type;	
	Texture2D texture;\
	float drift;
	float angle;
	float rotationSpeed;
	float phase;
};

// function definitions



#endif