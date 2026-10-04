#include <raylib/raylib.h>
#include <raylib/raymath.h>

#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>
#include <raylib/style_genesis.h>

#include "world.h"
#include "sim.h"
#include "view.h"
#include "ui.h"


int main(int argc, char **argv)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1600, 900, "N's N-Body");
	SetWindowMinSize(400, 300);
	DisableCursor();

	GuiLoadStyleGenesis();

	// --- camera setup

	Camera3D camera = {
		.position = (Vector3) {80.0f, 150.0f, 80.0f},
		.target = (Vector3) {0.0f, 0.0f, 0.0f},
		.up = (Vector3) {0.0f, 1.0f, 0.0f},
		.fovy = 45.0f,
		.projection = CAMERA_PERSPECTIVE
	};
	Vector3 camera_movement = {0};

	int camera_type = CAMERA_THIRD_PERSON;
	bool mouse_on = false;

	int target_body = 0;
	bool reference_center = true;
	Vector3 reference_frame = {0};

	// --- world space setup

	World w_space = sim_let_there_be_light();

	// --- side bar setup

	UISideBar sb = {
		.x = 0,
		.y = 0,
		.w = GetScreenWidth() * 0.2,
		.h = GetScreenHeight(),

		.margin_x = 8.0f,
		.margin_y = 16.0f,
		.padding = 12.0f,
		.spacing = 12.0f,

		.label_height = 20.0f,

		.font_size = 10
	};

	// --- main loop

	while (!WindowShouldClose()) {
		// mouse cursor
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			if (mouse_on) {
				DisableCursor();
				mouse_on = false;
			} else {
				EnableCursor();
				mouse_on = true;
			}
		}
		if (IsKeyReleased(KEY_T)) {
			if (camera_type == CAMERA_THIRD_PERSON) {
				camera_type = CAMERA_FREE;
				camera.up = (Vector3) {0.0f, 1.0f, 0.0f};
			} else {
				camera_type = CAMERA_THIRD_PERSON;
			}
		}

		// body selection
		if (IsKeyReleased(KEY_ONE))
			target_body = 0;
		if (IsKeyReleased(KEY_TWO))
			target_body = 1;
		if (IsKeyReleased(KEY_THREE))
			target_body = 2;

		if (IsKeyReleased(KEY_R))
			reference_center = !reference_center;

		if (camera_type == CAMERA_THIRD_PERSON)
			camera.target =  w_space.bodies[target_body].position;

		if (reference_center)
			reference_frame = (Vector3) {0};
		else
			reference_frame = w_space.bodies[target_body].position;

		UpdateCameraEx(&camera, camera_type, 50.0f, 0.003f);

		sb.h = GetScreenHeight();
		sb.w = GetScreenWidth() * 0.2;

		// --- do simulation

		sim_tick(&w_space, GetFrameTime() * TIME_FACTOR);

		// --- draw screen

		BeginDrawing(); {
			ClearBackground(BLACK);

			// --- draw what the camera sees

			BeginMode3D(camera); {

				// --- draw objects
				draw_bodies(&w_space, reference_frame);

			} EndMode3D();

			// --- write text

			ui_draw(&w_space, &sb);

		} EndDrawing();
	}

	CloseWindow();
	return 0;
}
