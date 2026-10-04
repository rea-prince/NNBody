#ifndef UI_H
#define UI_H

typedef struct {
	float x, y;
	float w, h;

	float margin_x;
	float margin_y;
	float padding;
	float spacing;

	float label_height;
	unsigned int elements;
	unsigned int font_size;
} UISideBar;

int ui_draw(World *w_space, UISideBar *sb);

#endif
