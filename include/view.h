#ifndef VIEW_H
#define VIEW_H

#define CAMERA_SPEED 1.0f

void draw_grid(Vector3 ref_frame,
			   int slices, float spacing, Color color);
int draw_bodies(World *w_space, Vector3 ref_frame);

#endif
