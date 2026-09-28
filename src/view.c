#ifndef VIEW_C
#define VIEW_C

#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <math.h>

#include "world.h"

void draw_grid(Vector3 ref_frame,
			   int slices, float spacing, Color color)
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


int draw_bodies(World *w_space, Vector3 ref_frame)
{
	for (int i = 0; i < w_space->n_bodies; i++) {
		Body *body = w_space->bodies + i;
		DrawSphere(body->position, body->radius, body->color);
		// draw trajectory
		DrawLine3D(
			body->position,
			Vector3Add(body->position, body->acceleration),
			RED
		);
	}

	draw_grid(ref_frame, 100, 10.0f, DARKGRAY);

	return 1;
}


#endif
