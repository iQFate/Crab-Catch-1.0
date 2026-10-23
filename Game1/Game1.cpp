// Game1.cpp : Defines the entry point for the application.
//

#include <raylib.h>
#include "Game1.h"

using namespace std;

int main()
{
	InitWindow(800, 500, "Window");

	int posX = 400 - 15 /2;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {


		if(IsKeyDown(KEY_D)) { posX += 1; }
		if(IsKeyDown(KEY_A)) { posX -= 1; }

		BeginDrawing();
		ClearBackground(BLUE);
		DrawRectangle(posX, 450, 30, 15, RED);
		EndDrawing();
	}
	return 0;
}
