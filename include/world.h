#ifndef WORLD_H
#define WORLD_H

#include <raylib/raylib.h>

#define BODIES 10
#define BODY_NAME_LEN 31 + 1

typedef struct {
	char name[BODY_NAME_LEN];
	Color color;
	float mass;
	float radius;
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	// gui controllers
	bool name_edit_mode;
    bool p_edit_mode[3]; // x, y, z
    bool v_edit_mode[3]; // x, y, z
    bool a_edit_mode[3]; // x, y, z
    bool m_edit_mode;
    bool r_edit_mode;
    bool color_dropdown_edit_mode;
    int color_dropdown_active;
} Body;

typedef struct {
	int n_bodies;
	int max_bodies;
	Body bodies[BODIES];
} World;

int world_add_body(World *w, char *name, Color color, float mass, float radius,
				   Vector3 position, Vector3 velocity, Vector3 acceleration);

#endif
