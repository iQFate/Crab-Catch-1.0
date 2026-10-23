// Game1.cpp : Defines the entry point for the application.
//

#include <raylib.h>
#include "Game1.h"
#include <vector>
using namespace std;

struct Garbage{
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	int speed;
};

int main() {
	InitWindow(800, 500, "Window");

	vector<Garbage>(TrashCan);

	Garbage bottle;
	bottle.posX = GetRandomValue(20, 780);
	bottle.posY = 0;
	bottle.sizeX = 20;
	bottle.sizeY = 40;
	bottle.speed = 2;
	TrashCan.push_back(bottle);

	int crabPosX = 400 - 60 /2;
	int  inatamitposY = 0;
	int SpawnPos = GetRandomValue(20, 780);
	int SpawnTime = 0;
	int SpawnInterval = GetRandomValue(60, 180);
	int Score = 0;
	

	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		SpawnTime ++;
		if(SpawnTime >= SpawnInterval){ 
			SpawnTime = 0;
			SpawnInterval = GetRandomValue(60, 180);
				Garbage bottle;
				bottle.posX = GetRandomValue(20, 780);
				bottle.posY = 0;
				bottle.sizeX = 20;
				bottle.sizeY = 40;
				bottle.speed = 2;
				TrashCan.push_back(bottle);
		}

		if(IsKeyDown(KEY_D)) { crabPosX += 4; }
		if(IsKeyDown(KEY_A)) { crabPosX -= 4; }
		if(crabPosX < 0) { crabPosX = 0;}
		if(crabPosX > 740) {crabPosX = 740;}
	
		
		Rectangle CrabRect = {static_cast<float>(crabPosX), 450, 60, 20};
		BeginDrawing();
		ClearBackground(BLUE);
		for(int i = 0; i < TrashCan.size(); i++){
			TrashCan[i].posY += TrashCan[i].speed;
			Rectangle bottleRect = {TrashCan[i].posX, TrashCan[i].posY,
				TrashCan[i].sizeX, TrashCan[i].sizeY };
				if (CheckCollisionRecs(CrabRect, bottleRect)){
					//Handle collison.
					Score++;
					TrashCan.erase(TrashCan.begin() + i);
					i--;
				} else {
    				// No collision, so draw the bottle
    				DrawRectangle(TrashCan[i].posX, TrashCan[i].posY,
                  TrashCan[i].sizeX, TrashCan[i].sizeY, SKYBLUE);
				}
			}

		DrawRectangle(crabPosX, 450, 60, 20, RED);
		DrawText(TextFormat("Score: %i", Score), 20, 20, 16, RED);
		
		//DrawRectangle(bottle.posX, bottle.posY, bottle.sizeX, bottle.sizeY, SKYBLUE);
		EndDrawing();
		
		
	}
	return 0;
}
