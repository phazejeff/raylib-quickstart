/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
using namespace std;
#include <vector>
#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "BALLS.");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	SetTargetFPS(144);

	// Load a texture from the resources directory
	Texture obama = LoadTexture("President_Barack_Obama-1825499922.jpg");
	Texture lebron = LoadTexture("2544-1359528295.png");

	Vector2 posObama = {
			400,
			200
		};

	Vector2 posLebron = {
			800,
			200
		};

	int speed = 500;
	vector<Vector2> lasersPos;
	double laserFireWaitTime = 0.5;

	double lastLaserFired = 0;

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Obama says: Raylib!", 200,200,20,WHITE);

		// draw our texture to the screen
		// DrawTexture(obama, 400, 200, WHITE);
		if (IsKeyDown(KEY_W)) {
			posObama.y = posObama.y - speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S)) {
			posObama.y = posObama.y + speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_A)) {
			posObama.x = posObama.x - speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_D)) {
			posObama.x = posObama.x + speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP)) {
			posLebron.y = posLebron.y - speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN)) {
			posLebron.y = posLebron.y + speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_LEFT)) {
			posLebron.x = posLebron.x - speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_RIGHT)) {
			posLebron.x = posLebron.x + speed * GetFrameTime();
		}

		if (IsKeyPressed(KEY_SPACE)) {
			if (GetTime() > lastLaserFired + laserFireWaitTime) {
				lastLaserFired = GetTime();
				Vector2 lPos = posObama;
				lPos.y = lPos.y + 85;
				lPos.x = lPos.x + 30;
				lasersPos.push_back(lPos); 
			}   
		}
		DrawTextureEx(obama, posObama, 0, 0.2, WHITE);
		DrawTextureEx(lebron, posLebron, 0, 0.2, WHITE);
		for (int i = 0; i < lasersPos.size(); i++) {
			lasersPos[i].x = lasersPos[i].x + speed * GetFrameTime();
			DrawRectangle(lasersPos[i].x, lasersPos[i].y, 100, 10, RED);	  
		}
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(obama);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
