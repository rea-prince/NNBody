#include <raylib/raylib.h>
#include <raylib/raygui.h>

#include "world.h"
#include "sim.h"

int main(int argc, char **argv)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 600, "N's N-Body");
	SetWindowMinSize(400, 300);
	DisableCursor();

	// ---

	Camera3D camera = {
		.position = (Vector3) {0.0f, 100.0f, 100.0f},
		.target = (Vector3) {0.0f, 0.0f, 0.0f},
		.up = (Vector3) {0.0f, 1.0f, 0.0f},
		.fovy = 45.0f,
		.projection = CAMERA_PERSPECTIVE
	};

	// ---

	World w_space = {
		.max_bodies = BODIES
	};
	world_add_body(&w_space,
		10.0f, 1.0f,
		(Vector3) {0.1f, 0.2f, 0.0f},
		(Vector3) {0.0f, 0.0f, 0.0f},
		(Vector3) {0.0f, 0.0f, 0.0f}
	);

	// ---

	while (!WindowShouldClose()) {
		// update

		UpdateCamera(&camera, CAMERA_FREE);

		// ---

		// do simulation


		sim_tick(&w_space, GetFrameTime());

		// ---

		// draw simulation

		BeginDrawing(); {
			ClearBackground(RAYWHITE);

			// ---

			BeginMode3D(camera); {

				// draw objects
				for (int i = 0; i < w_space.n_bodies; i++) {
					Body *body = w_space.bodies + i;
					DrawSphere(body->position, body->radius, LIME);

					TraceLog(LOG_INFO,
						"body: %d: pos=(%.2f, %.2f, %.2f), radius=%.2f",
						i,
						body->position.x,
						body->position.y,
						body->position.z,
						body->radius
					);
				}

				DrawGrid(100, 1.0f);
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
