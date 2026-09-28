#ifndef WORLD_C
#define WORLD_C

#include "world.h"

int world_add_body(World *w, Color color, float mass, float radius,
				   Vector3 position, Vector3 velocity, Vector3 acceleration)
{
	if (w->n_bodies == w->max_bodies) {
		return 0;
	}
	w->bodies[w->n_bodies++] = (Body) {
		.color = color,
		.mass = mass,
		.radius = radius,
		.position = position,
		.velocity = velocity,
		.acceleration = acceleration
	};
	return 1;
}



#endif
