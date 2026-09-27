#ifndef WORLD_C
#define WORLD_C

#include "world.h"

int world_add_body(World *w, float mass, float radius, Vector3 velocity,
				   Vector3 acceleration, Vector3 position)
{
	if (w->n_bodies == w->max_bodies) {
		return 0;
	}
	w->bodies[w->n_bodies++] = (Body) {
		.mass = mass,
		.radius = radius,
		.position = position,
		.velocity = velocity,
		.acceleration = acceleration
	};
	return 1;
}



#endif
