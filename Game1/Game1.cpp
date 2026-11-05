// Game1.cpp : Defines the entry point for the application.
//

#include <raylib.h>
#include "Game1.hpp"
#include <vector>
using namespace std;
#include <cmath>



Garbage::Garbage(const Texture2D& bottleTexture, const Texture2D& canTexture, const Texture2D& bombTexture) {
    this->type = GetRandomValue(0, 2); //Random object spawn
	TraceLog(LOG_INFO, "NEW GARBAGE CREATED: Type = %d", this->type);
	this->posY = GetRandomValue(-300, -50);
	this->posX = GetRandomValue(25,525);
	this->speed = 0;
	this->drift = 0.0f;
	this->angle = GetRandomValue(-15, 15);
	this->rotationSpeed = GetRandomValue(-10, 10) / 10.0f;
	this->phase = GetRandomValue(0, 628) / 100.0f;

	if (this->type == 0) { //bottle
		this->texture = bottleTexture;
		this->sizeX = 50;
		this->sizeY = 65;
		this->speed = 5;
	} 
	else if (this->type == 1) { //can
		this->texture = canTexture;
		this->sizeX = 40;
		this->sizeY = 60;
		this->speed = 6;
	} 
	else if (this->type == 2) { //bomb
		this->texture = bombTexture;
		this->sizeX = 40;
		this->sizeY= 40;
		this->speed = 9;
	}
}

void Garbage::update() {
    this->posY += this->speed;
    this->phase += 0.05f;
    this->angle = sin(this->phase) * 15.0f;
}

void Garbage::draw() {
		DrawTexturePro(
    this->texture,
    {0, 0,
     static_cast<float>(this->texture.width),
     static_cast<float>(this->texture.height)},
    {
        static_cast<float>(this->posX + this->sizeX / 2),
        static_cast<float>(this->posY + this->sizeY / 2),
        static_cast<float>(this->sizeX),
        static_cast<float>(this->sizeY)
    },
    {
        static_cast<float>(this->sizeX) / 2.0f,
        static_cast<float>(this->sizeY) / 2.0f
    },
    this->angle,
    WHITE
);
}

Rectangle Garbage::getCollisionRect() const {
	Rectangle rect = {
	static_cast<float>(this->posX + 2),
	static_cast<float>(this->posY + 5),
	static_cast<float>(this->sizeX -5),
	static_cast<float>(this->sizeY - 10)
	};

	return rect;
}

int Garbage::getType() const {
	return this->type;
}

int Garbage::getPosX() const {
    return this->posX;
}

int Garbage::getPosY() const {
    return this->posY;
}


	

int main() {
	InitWindow(600, 700, "Window");
	InitAudioDevice();

	Music backgroundMusic = LoadMusicStream("Game1/ABraveNewWorld.mp3");

	SetMusicVolume(backgroundMusic, 0.20f);
	PlayMusicStream(backgroundMusic);
	Texture2D crabTexture = LoadTexture("Game1/Crab1.png");
	Texture2D crabTexture2 = LoadTexture("Game1/Crab2.png");
	Texture2D bottleTexture = LoadTexture("Game1/waterbottle.png");
	Texture2D canTexture = LoadTexture("Game1/can.png");
	Texture2D bombTexture = LoadTexture("Game1/bomb.png");
	Texture2D explosionTexture = LoadTexture("Game1/explosion.png");//  bomb art - 1 life
	Texture2D shrimpTexture = LoadTexture("Game1/shrimp.png"); //extra health shrimp	
	Texture2D backgroundTexture = LoadTexture("Game1/water.png");

	std::vector<Garbage> TrashCan;
	std::vector<Shrimp> ShrimpCan;



	int crabPosX = 400 - 60 /2;
	int  inatamitposY = 0;
	int SpawnPos = GetRandomValue(20, 680);
	int SpawnTime = 0;
	int SpawnInterval = GetRandomValue(20,180);
	int ShrimpSpawnTime = 0;
	int ShrimpSpawnInterval = GetRandomValue(1000,7000);
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

		UpdateMusicStream(backgroundMusic);

		SpawnTime++;
		if (SpawnTime >= SpawnInterval) {

		int SpawnAmount = GetRandomValue(1, 4);
		for (int i = 0; i < SpawnAmount; i++) {
			TrashCan.emplace_back(bottleTexture, canTexture, bombTexture);
		}
		SpawnTime = 0;
		if (GetRandomValue(0, 4) == 0) {
			SpawnInterval = GetRandomValue(90, 180);
		} else {
			SpawnInterval = GetRandomValue(5, 40);
		}
		
	}
		

		ShrimpSpawnTime++;

		if (ShrimpSpawnTime >= ShrimpSpawnInterval) {
			Shrimp shrimp;
			shrimp.posX = GetRandomValue(25, 525);
			shrimp.posY = -50;
			shrimp.speed = 11;
			shrimp.sizeX = 50;
			shrimp.sizeY = 40;
			shrimp.texture = shrimpTexture;

			ShrimpCan.push_back(shrimp);

			ShrimpSpawnTime = 0;
		}

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
		DrawTexturePro(
			backgroundTexture,
			{0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height},
			{0, 0, 600, 700},
			{0, 0},
			0.0f,
			WHITE
		);
		ClearBackground(SKYBLUE);
		DrawRectangle(0, 625, 600, 75, BEIGE);

					for (int i = 0; i < ShrimpCan.size(); i++) {

				ShrimpCan[i].posY += ShrimpCan[i].speed;

				Rectangle shrimpRect = {
					static_cast<float>(ShrimpCan[i].posX),
					static_cast<float>(ShrimpCan[i].posY),
					static_cast<float>(ShrimpCan[i].sizeX),
					static_cast<float>(ShrimpCan[i].sizeY)
				};

				if (CheckCollisionRecs(CrabRect, shrimpRect)) {

					lives++;  // Crab eats shrimp, gains one life!

					ShrimpCan.erase(ShrimpCan.begin() + i);
					i--;
					continue;
				}

				DrawTexturePro(
					ShrimpCan[i].texture,
					{0, 0,
					static_cast<float>(shrimpTexture.width),
					static_cast<float>(shrimpTexture.height)},
					shrimpRect,
					{0, 0},
					0.0f,
					WHITE
				);

				if (ShrimpCan[i].posY > 700) {
					ShrimpCan.erase(ShrimpCan.begin() + i);
					i--;
				}
			}
			
		for(int i = 0; i < TrashCan.size(); i++){
			TrashCan[i].update();
			Rectangle bottleRect = TrashCan[i].getCollisionRect();
				if (CheckCollisionRecs(CrabRect, bottleRect)){
					//Handle collison.
					if (TrashCan[i].getType() == 2) {
						if (lives > 0) {
						lives--;
						}

						    explosionActive = true;
							explosionTimer = 0;
							explosionX = TrashCan[i].getPosX();
							explosionY = TrashCan[i].getPosY();
					} else {
					Score++;
					}
					TrashCan.erase(TrashCan.begin() + i);
					i--;
				} else {
					TrashCan[i].draw();
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
