#include <stdio.h>
#include <raylib/raylib.h>
#include <raylib/raygui.h>

int main(int argc, char **argv)
{
	InitWindow(800, 400, "N-Body");

	while (!WindowShouldClose()) {
		BeginDrawing(); {
			ClearBackground(RAYWHITE);
			DrawText("Wow my first window!", 190, 200, 20, LIGHTGRAY);

		} EndDrawing();
	}

	CloseWindow();
	return 0;
}
