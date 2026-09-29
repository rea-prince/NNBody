#ifndef VIEW_C
#define VIEW_C

#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <math.h>

#include "raylib/raygui.h"
#include "world.h"

#define VIS_VEL_SCALE 10.0f
#define VIS_ACC_SCALE 1000.0f
#define VECTOR_RADIUS 1.0f

void draw_grid(Vector3 ref_frame,
			   int slices, float spacing, Color color)
{
	float ends = slices * spacing;

	for (int i = -slices; i <= slices; i++)
	{

		Color line_color = color;

		// z axis
		DrawLine3D(
			(Vector3){
				i * spacing + ref_frame.x,
				0 + ref_frame.y,
				-ends + ref_frame.z
			},
			(Vector3){
				i * spacing + ref_frame.x,
				0 + ref_frame.y,
				ends + ref_frame.z
			},
			line_color
		);

		// x axis
		DrawLine3D(
			(Vector3){
				-ends + ref_frame.x,
				0 + ref_frame.y,
				i * spacing + ref_frame.z
			},
			(Vector3){
			 	ends + ref_frame.x,
				0 + ref_frame.y,
				i * spacing + ref_frame.z
			},
			line_color
		);
	}
}

int draw_body_vector(float radius, Vector3 position,
					 Vector3 vector, Color color)
{
	// draw velocity
	// normalize velocity vector -> scale it by the radius
	// -> move it to real world position -> draw from there
	// that way it won't be blocked by the body
	Vector3 surface = Vector3Add(
		position,
 		Vector3Scale(
			Vector3Normalize(vector),
			radius
		)
	);
	Vector3 vector_end = Vector3Add(
		surface,
		vector
	);

	DrawLine3D(
		surface,
		vector_end,
		color
	);

	DrawSphere(vector_end, VECTOR_RADIUS, color);

	return 1;
}

int draw_bodies(World *w_space, Vector3 ref_frame)
{
	for (int i = 0; i < w_space->n_bodies; i++) {
		Body *body = w_space->bodies + i;
		DrawSphere(body->position, body->radius, body->color);

		draw_body_vector(
			body->radius,
			body->position,
			body->velocity,
			RED
		);
		draw_body_vector(
			body->radius,
			body->position,
			body->acceleration,
			SKYBLUE
		);

		// DrawSphere(acceleration_end, body->radius * 0.15f, SKYBLUE);
	}

	draw_grid(ref_frame, 100, 100.0f, DARKGRAY);

	return 1;
}

int draw_gui(World *w_space)
{

	GuiPanel(
		(Rectangle) {0, 0, 250, GetScreenHeight()},
		"#001#Bodies"
	);
	const char *fps_text = TextFormat("FPS: %i", GetFPS());
	const char *frame_time = TextFormat("FrameTime: %02.02f", GetFrameTime());
	const char *controls = "Target - [1, ..., n]\nCamera - T\nReference frame - R";
	DrawText(fps_text, 10, 30, 20, WHITE);
	DrawText(frame_time, 10, 50, 20, WHITE);
	DrawText(controls, 10, 70, 20, WHITE);

	for (int i = 0; i < w_space->n_bodies; i++) {
		// container
			// index

			// mass

			// radius

			//

	}

	// GuiButton(
	// 	(Rectangle) {24, 24, 160, 30},
	// 	"#001#Test"
	// );

	return 1;
}


#endif
