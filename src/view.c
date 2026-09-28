#ifndef VIEW_C
#define VIEW_C

#include <raylib/raylib.h>
#include <math.h>

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


#endif
