#include <raylib/raylib.h>
#include <raylib/raymath.h>

#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>

#include "world.h"
#include "sim.h"
#include "view.h"

int main(int argc, char **argv)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 600, "N's N-Body");
	SetWindowMinSize(400, 300);
	DisableCursor();

	// ---

	Camera3D camera = {
		.position = (Vector3) {80.0f, 150.0f, 80.0f},
		.target = (Vector3) {0.0f, 0.0f, 0.0f},
		.up = (Vector3) {0.0f, 1.0f, 0.0f},
		.fovy = 45.0f,
		.projection = CAMERA_PERSPECTIVE
	};

	int camera_type = CAMERA_THIRD_PERSON;
	bool mouse_on = false;

	int target_body = 0;
	bool lock_position = false;

	// ---

	World w_space = {
		.max_bodies = BODIES
	};
	world_add_body(&w_space,
		81.25f, 6.38f,
		(Vector3) {0.0f, 0.0f, 0.0f},
		(Vector3) {0.0f, 0.0f, 0.0f},
		(Vector3) {0.0f, 0.0f, 0.0f}
	);

	world_add_body(&w_space,
		1.0f, 1.74f,
		(Vector3) {0.0f, 0.0f, -200.0f},
		(Vector3) {0.63737f, 0.0f, 0.0f},
		(Vector3) {0.0f, 0.0f, 0.0f}
	);
	world_add_body(&w_space,
		1.0f, 1.74f,
		(Vector3) {0.0f, 0.0f, 200.0f},
		(Vector3) {-0.63737f, 0.0f, 0.0f},
		(Vector3) {0.0f, 0.0f, 0.0f}
	);
	// ---

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
		// orbital mode
		if (IsKeyReleased(KEY_T)) {
			if (camera_type == CAMERA_THIRD_PERSON)
				camera_type = CAMERA_FREE;
			else
				camera_type = CAMERA_THIRD_PERSON;
		}
		// lock mode
		if (IsKeyReleased(KEY_L)) {
			lock_position = !lock_position;
		}
		// body selection
		if (IsKeyReleased(KEY_ONE))
			target_body = 0;
		if (IsKeyReleased(KEY_TWO))
			target_body = 1;
		if (IsKeyReleased(KEY_THREE))
			target_body = 2;

		if (camera_type == CAMERA_THIRD_PERSON) {
			camera.target =  w_space.bodies[target_body].position;
		}

		UpdateCamera(&camera, camera_type);

		// ---

		// do simulation

		sim_tick(&w_space, GetFrameTime() * TIME_FACTOR);

		// ---

		// draw simulation

		BeginDrawing(); {
			ClearBackground(BLACK);

			// ---

			BeginMode3D(camera); {

				// draw objects
				for (int i = 0; i < w_space.n_bodies; i++) {
					Body *body = w_space.bodies + i;
					DrawSphere(body->position, body->radius, LIME);

					// TraceLog(LOG_INFO,
					// 	"body: %d: pos=(%.2f, %.2f, %.2f), radius=%.2f, acceleration=%.2f",
					// 	i,
					// 	body->position.x,
					// 	body->position.y,
					// 	body->position.z,
					// 	body->radius,
					// 	body->acceleration
					// );
				}

				draw_grid(w_space.bodies[target_body].position,100, 10.0f, DARKGRAY);
			} EndMode3D();

			// ---

			const char *fps_text = TextFormat("FPS: %i", GetFPS());
			const char *frame_time = TextFormat("FrameTime: %02.02f", GetFrameTime());
			DrawText(fps_text, 10, 20, 20, DARKGRAY);
			DrawText(frame_time, 10, 40, 20, DARKGRAY);


		} EndDrawing();
	}

	CloseWindow();
	return 0;
}
