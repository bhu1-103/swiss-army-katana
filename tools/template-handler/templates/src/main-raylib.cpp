#include <raylib.h>

int main()
{
    InitWindow(1280,720, "idk");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
	}
	CloseWindow();
    
    return 0;
}
