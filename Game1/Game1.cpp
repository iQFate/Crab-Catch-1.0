// Game1.cpp : Defines the entry point for the application.
//

#include <raylib.h>
#include "Game1.hpp"
#include <vector>
using namespace std;


void spawnGarbage(vector<Garbage>& TrashCan){ // Spawn Garbage Function
		SpawnTime ++;
		if(SpawnTime >= SpawnInterval){ 
			SpawnTime = 0;
			SpawnInterval = GetRandomValue(5, 100);
				Garbage bottle;
				bottle.posX = GetRandomValue(25, 575);
				bottle.posY = 0;
				bottle.sizeX = 50;
				bottle.sizeY = 65;
				bottle.speed = 5;
				bottle.type = 0;
				TrashCan.push_back(bottle);

		}

		SpawnTime ++;
		if(SpawnTime >= SpawnInterval){ 
			SpawnTime = 0;
			SpawnInterval = GetRandomValue(5, 100);
				Garbage can;
				can.posX = GetRandomValue(25, 575);
				can.posY = 0;
				can.sizeY = 60;
				can.sizeX = 40;
				can.speed = 5;
				can.type = 1;
				TrashCan.push_back(can);

		}

		SpawnTime ++;
		if(SpawnTime >= SpawnInterval){ 
			SpawnTime = 0;
			SpawnInterval = GetRandomValue(5, 100);
				Garbage bomb;
				bomb.posX = GetRandomValue(25, 575);
				bomb.posY = 0;
				bomb.sizeY = 40;
				bomb.sizeX = 40;
				bomb.speed = 5;
				bomb.type = 2;
				TrashCan.push_back(bomb);

		}
	}

int main() {
	InitWindow(600, 700, "Window");
	Texture2D crabTexture = LoadTexture("Game1/Crab1.png");
	Texture2D crabTexture2 = LoadTexture("Game1/Crab2.png");
	Texture2D bottleTexture = LoadTexture("Game1/waterbottle.png");
	Texture2D canTexture = LoadTexture("Game1/can.png");
	Texture2D bombTexture = LoadTexture("Game1/bomb.png");
	Texture2D explosionTexture = LoadTexture("Game1/explosion.png");

	vector<Garbage>(TrashCan);


	int crabPosX = 400 - 60 /2;
	int  inatamitposY = 0;
	int SpawnPos = GetRandomValue(20, 680);
	int SpawnTime = 0;
	int SpawnInterval = GetRandomValue(60, 180);
	int Score = 0;
	int crabFrame = 0;
	int animationTimer = 0;
	int lives = 4;
	bool explosionActive = false;
	int explosionTimer = 0;
	int explosionX = 0;
	int explosionY = 0;
	

	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		spawnGarbage(TrashCan);


		if(IsKeyDown(KEY_D)) { crabPosX += 6.5; }
		if(IsKeyDown(KEY_A)) { crabPosX -= 6.5; }
		if(IsKeyDown(KEY_A) || IsKeyDown(KEY_D)){
			animationTimer++;

			if (animationTimer >= 10) {
				animationTimer = 0;
				crabFrame = 1 - crabFrame;
			} 
		} 
		else {
				crabFrame = 0;
				animationTimer = 0;
			}
		

		if(crabPosX < -10) { crabPosX = -10;}
		if(crabPosX > 485) {crabPosX = 485;}
	
		
		Rectangle CrabRect = {static_cast<float>(crabPosX + 32), 600, 62, 5};
		BeginDrawing();
		ClearBackground(SKYBLUE);
		for(int i = 0; i < TrashCan.size(); i++){
			TrashCan[i].posY += TrashCan[i].speed;
			Rectangle bottleRect = {TrashCan[i].posX +2, TrashCan[i].posY +5,
				TrashCan[i].sizeX-5, TrashCan[i].sizeY-10 };
				if (CheckCollisionRecs(CrabRect, bottleRect)){
					//Handle collison.
					if (TrashCan[i].type == 2) {
						if (lives > 0) {
						lives--;
						}

						    explosionActive = true;
							explosionTimer = 0;
							explosionX = TrashCan[i].posX;
							explosionY = TrashCan[i].posY;
					} else {
					Score++;
					}
					TrashCan.erase(TrashCan.begin() + i);
					i--;
				} else {
    				if (TrashCan[i].type == 0) {
						DrawTexturePro(
							bottleTexture,
							{0, 0, static_cast<float>(bottleTexture.width), static_cast<float>(bottleTexture.height)},
							{static_cast<float>(TrashCan[i].posX), static_cast<float>(TrashCan[i].posY),
							static_cast<float>(TrashCan[i].sizeX), static_cast<float>(TrashCan[i].sizeY)},
							{0, 0}, 25.0f, WHITE);
				}	if (TrashCan[i].type == 1) {
						DrawTexturePro(
							canTexture,
							{0, 0, static_cast<float>(canTexture.width), static_cast<float>(canTexture.height)},
							{static_cast<float>(TrashCan[i].posX), static_cast<float>(TrashCan[i].posY),
							static_cast<float>(TrashCan[i].sizeX), static_cast<float>(TrashCan[i].sizeY)},
							{0, 0}, -15.0f, WHITE);
				}
					if (TrashCan[i].type == 2)
						DrawTexturePro(
							bombTexture,
							{0, 0, static_cast<float>(bombTexture.width), static_cast<float>(bombTexture.height)},
							{static_cast<float>(TrashCan[i].posX), static_cast<float>(TrashCan[i].posY),
							static_cast<float>(TrashCan[i].sizeX), static_cast<float>(TrashCan[i].sizeY)},
							{0, 0}, 0.0f, WHITE);
				}
			}

		if (crabFrame == 0) {
			DrawTextureEx(crabTexture, {static_cast<float>(crabPosX), 560.0f}, 0.0f, 4.0f, WHITE);
		} else {
			DrawTextureEx(crabTexture2, {static_cast<float>(crabPosX), 560.0f}, 0.0f, 4.0f, WHITE);
		}
		if (explosionActive) {
			explosionTimer++;

			float explosionSize = 40.0f + explosionTimer * 3.0f;

			DrawTexturePro(
				explosionTexture,
				{0, 0, static_cast<float>(explosionTexture.width),
					static_cast<float>(explosionTexture.height)},
				{static_cast<float>(explosionX),
				static_cast<float>(explosionY),
				explosionSize, explosionSize},
				{explosionSize / 2.0f, explosionSize / 2.0f},
				0.0f,
				WHITE
			);

			if (explosionTimer >= 30) {
				explosionActive = false;
			}
		}
		
		DrawRectangleLinesEx(CrabRect, 2, GREEN);
		DrawText(TextFormat("Score: %i", Score), 20, 20, 24, GREEN);
		DrawText(TextFormat("Lives: %i", lives), 20, 45, 24, RED);
		if (lives == 0) {
		DrawText(TextFormat("Game Over!", lives), 30, 300, 100, RED);
		}
		
		//DrawRectangle(bottle.posX, bottle.posY, bottle.sizeX, bottle.sizeY, SKYBLUE);
		EndDrawing();
		
		
	}
	return 0;
}
