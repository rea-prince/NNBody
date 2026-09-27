#ifndef WORLD_H
#define WORLD_H

#include <raylib/raylib.h>

#define BODIES 10

typedef struct {
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

int world_add_body(World *w, float mass, float radius, Vector3 velocity,
				   Vector3 acceleration, Vector3 position);

#endif
