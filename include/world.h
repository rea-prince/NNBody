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
} Body;

typedef struct {
	int n_bodies;
	int max_bodies;
	Body bodies[BODIES];
} World;

int world_add_body(World *w, char *name, Color color, float mass, float radius,
				   Vector3 position, Vector3 velocity, Vector3 acceleration);

#endif
