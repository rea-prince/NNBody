#include <raylib/raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>

#include "world.h"
#include "sim.h"

void draw_grid(int slices, float spacing, Color color)
{
	float ends = slices * spacing;

	for (int i = -slices; i <= slices; i++)
	{

		Color line_color = color;

		// 1.0 = farthest from center; fade by at most 0.7
		float center_distance = fabs((float) i / slices);
		float center_fade = 1.0f - (center_distance * 1.0f);

		line_color.a = (unsigned char) (color.a * center_fade);

		// z axis
		DrawLine3D(
			(Vector3){ i * spacing, 0, -ends },
			(Vector3){ i * spacing, 0, ends },
			line_color
		);

		// x axis
		DrawLine3D(
			(Vector3){ -ends, 0, i * spacing },
			(Vector3){ ends, 0, i * spacing },
			line_color
		);
	}
}

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

	int camera_type = CAMERA_ORBITAL;
	bool mouse_on = false;
	int target_body = 0;

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
		// update

		if (IsKeyReleased(KEY_X)) {
			if (mouse_on) {
				DisableCursor();
				mouse_on = false;
			} else {
				EnableCursor();
				mouse_on = true;
			}
		}

		if (IsKeyReleased(KEY_O)) {
			if (camera_type == CAMERA_ORBITAL)
				camera_type = CAMERA_FREE;
			else
				camera_type = CAMERA_ORBITAL;
		}

		if (camera_type == CAMERA_ORBITAL) {
			camera.target =  w_space.bodies[target_body].position;
		}

		if (IsKeyReleased(KEY_ONE))
			target_body = 0;
		if (IsKeyReleased(KEY_TWO))
			target_body = 1;
		if (IsKeyReleased(KEY_THREE))
			target_body = 2;

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

				draw_grid(100, 10.0f, DARKGRAY);
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
