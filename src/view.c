#ifndef VIEW_C
#define VIEW_C

#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <raylib/raygui.h>

#include "world.h"

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

#endif
