#ifndef UI_C
#define UI_C

#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <raylib/raygui.h>

#include "world.h"
#include "ui.h"

#define N_PROPERTIES 6
#define COL_OFFSET 150.0f // this is completely arbitrary

// draw property based on container
int ui_draw_property(UISideBar *sb, int x, int y, int w, int h,
					 const char *label, const char *content)
{
	float prop_x = x + w - sb->padding - COL_OFFSET;

	GuiLabel((Rectangle)
		{ x, y, 120, sb->label_height },
		label
	);
	GuiLabel((Rectangle)
		{ prop_x, y, COL_OFFSET, sb->label_height },
		content
	);
	return 1;
}

int ui_draw(World *w_space, UISideBar *sb)
{
	// --- performance group

	float perf_x = sb->x + sb->margin_x;
	float perf_y = sb->y + sb->margin_y;

	// performance length and width
	// sb width - margin on left and right
	float perf_w = sb->w - (sb->margin_x * 2);
	// rows of text + padding + spacing
	float perf_h = (sb->padding * 2) + (sb->label_height * 2);

	GuiGroupBox((Rectangle)
		{ perf_x, perf_y, perf_w, perf_h },
		"Performance"
	);

	// performance properties

	float perf_content_x = perf_x + sb->padding; // group x + padding
	float perf_row1_y = perf_y + sb->padding;    // group y + padding
	float perf_row2_y = perf_row1_y + sb->label_height; // row 1 + height

	ui_draw_property(sb, perf_content_x, perf_row1_y, perf_w, perf_h,
		"Framerate", TextFormat("%i FPS", GetFPS()));
	ui_draw_property(sb, perf_content_x, perf_row2_y, perf_w, perf_h,
		"Frametime", TextFormat("%.2f ms", GetFrameTime() * 1000.0f));

	// --- world group

	float world_x = perf_x;
	float world_y = perf_y + perf_h + sb->spacing;

	float world_w = perf_w;
	float world_h = perf_h;

	GuiGroupBox((Rectangle)
		{ world_x, world_y, world_w, world_h},
		 "World"
	);

	float world_content_x = perf_content_x;
	float world_row1_x = world_y + sb->padding;    // group y + padding
	float world_row2_y = world_row1_x + sb->label_height; // row 1 + height

	ui_draw_property(sb, world_content_x, world_row1_x, world_w, world_h,
		"Biggy G", TextFormat("%.2f (N*m^2)/kg^2", w_space->GRAV_CONSTANT));
	ui_draw_property(sb, world_content_x, world_row2_y, world_w, world_h,
		"Time Scale", TextFormat("%.2f x", w_space->TIME_SCALE));

	// --- bodies group

	float body_x = perf_x;
	float body_y = world_y + world_h + sb->spacing;

	float body_w = perf_w;
	float body_h =
		(sb->padding * 2) + (sb->label_height * N_PROPERTIES) +
		(sb->label_height * N_PROPERTIES + sb->spacing) * (w_space->n_bodies - 1);

	GuiGroupBox((Rectangle)
		{ body_x, body_y, body_w, body_h},
		 "Bodies"
	);

	float body_content_x = perf_content_x;
	float body_row_y = body_y + sb->padding;

	for (int i = 0; i < w_space->n_bodies; i++) {
		Body *body = &w_space->bodies[i];
		ui_draw_property(sb,
			body_content_x, body_row_y,
			body_w, body_h,
			"Name", body->name
		);
		ui_draw_property(sb,
			body_content_x, body_row_y + sb->label_height*1,
			body_w, body_h,
			"Mass", TextFormat("%.2f m",body->mass)
		);
		ui_draw_property(sb,
			body_content_x, body_row_y + sb->label_height*2,
			body_w, body_h,
			"Radius", TextFormat("%.2f kg",body->radius)
		);
		ui_draw_property(sb,
			body_content_x, body_row_y + sb->label_height*3,
			body_w, body_h,
			"Position", TextFormat("%.2f %.2f %.2f", body->position.x, body->position.y, body->position.z)
		);
		ui_draw_property(sb,
			body_content_x, body_row_y + sb->label_height*4,
			body_w, body_h,
			"Velocity", TextFormat("%.2f", Vector3Length(body->velocity))
		);
		ui_draw_property(sb,
			body_content_x, body_row_y + sb->label_height*5,
			body_w, body_h,
			"Acceleration", TextFormat("%.2f", Vector3Length(body->acceleration))
		);
		body_row_y += (sb->label_height*6) + sb->spacing;
	}

	return 1;
}


#endif
