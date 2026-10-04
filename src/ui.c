#ifndef UI_C
#define UI_C

#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <raylib/raygui.h>

#include "world.h"
#include "ui.h"

int ui_draw(World *w_space, UISideBar *sb)
{
	// performance
	float perf_x = sb->x + sb->margin_x;
	float perf_y = sb->y + sb->margin_y;

	// sb width - margin on left and right
	float perf_w = sb->w - (sb->margin_x * 2);
	//  rows of text + padding + spacing
	float perf_h = (sb->padding * 2) + (sb->label_height * 2) + sb->spacing;

	GuiGroupBox((Rectangle){ perf_x, perf_y, perf_w, perf_h }, "Performance");

	float perf_content_x = perf_x + sb->padding; // group x + padding
	float perf_row1_y = perf_y + sb->padding;    // group y + padding
	float perf_row2_y =
		perf_row1_y + sb->label_height + sb->spacing; // row 1 +  spacing + height

	// right aligned
	float value_col_w = 80.0f; // this is completely arbitrary
	float perf_val_x = perf_x + perf_w - sb->padding - value_col_w;

	GuiLabel((Rectangle)
		{ perf_content_x, perf_row1_y,
		  120, sb->label_height },
		"Frames Per Second"
	);
	GuiLabel((Rectangle)
		{ perf_content_x, perf_row2_y,
		  120, sb->label_height },
		"Frametime"
	);
	GuiLabel((Rectangle)
		{ perf_val_x, perf_row1_y,
		  value_col_w, sb->label_height },
		TextFormat("%i FPS", GetFPS())
	);
	GuiLabel((Rectangle)
		{ perf_val_x, perf_row2_y,
		  value_col_w, sb->label_height },
		TextFormat("%.2f ms", GetFrameTime() * 1000.0f)
	);

	// bodies
// 	float bodies_x = perf_x;
// 	float bodies_y = perf_y + perf_h + sb->spacing; // might wanna change spacing
//
// 	float total_cards_h =
// 		(w_space->n_bodies * (sb->body_card_height + sb->spacing));
// 	float bodies_h = total_cards_h + (sb->padding * 2);
//
// 	GuiGroupBox((Rectangle){ bodies_x, bodies_y, perf_w, bodies_h }, "Bodies");
//
// 	float card_x = bodies_x + sb->padding;
// 	float current_card_y = bodies_y + sb->padding;
//
// 	for (int i = 0; i < w_space->n_bodies; i++) {
// 		// draw_body_card(&w_space->bodies[i], sb, card_x, current_card_y, i, w_space);
// 		current_card_y += sb->body_card_height + sb->spacing;
// 	}

	return 1;
}


#endif
