#ifndef SIM_C
#define SIM_C

#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <math.h>

#include "world.h"
#define GRAV_CONSTANT 1.0f

// update position and velocty, and compute for new acceleration
int sim_tick(World *w, double time)
{
	// for a second, i was worried this would not work because of ordering,
	// before i remembered that a property of vectorspaces is commutativity!

	int n_b = w->n_bodies;

	// TraceLog(LOG_INFO,
	// 	"ticking at delta time=%.10lf",
	// 	time
	// );

	for (int i = 0; i < n_b; i++) {
		Body *body_i = w->bodies + i;
		body_i->acceleration = (Vector3) {0};

		// compute for new acceleration
		// a_i = 1/m_i \sum^{N - 1}_{j = 0, j \neq i} \frac{G m_i m_j}{r^2} \cdot \frac{\vec{r}}{r}
		//     = \sum^{N - 1}_{j = 0, j \neq i} \frac{G m_j}{|r|^3} \cdot \vec{r}

		// TO DO: optimize this

		for (int j = 0; j < n_b; j++) {
			if (j == i)
				continue;

			Body *body_j = w->bodies + j;

			// get normalized direction
			Vector3 displacement = Vector3Subtract(body_j->position, body_i->position);
			float distance = Vector3Length(displacement);
			if (distance == 0)
				continue;
			Vector3 r = Vector3Normalize(displacement);

			// get magnitude of acceleration
			float acceleration_scalar = fabs(
				GRAV_CONSTANT * (body_j->mass) /
				powf(distance, 2));

			// add to body's acceleration
			body_i->acceleration.x += r.x * acceleration_scalar;
			body_i->acceleration.y += r.y * acceleration_scalar;
			body_i->acceleration.z += r.z * acceleration_scalar;
		}

	}

	// update positions and velocities

	for (int i = 0; i < n_b; i++) {
		Body *body = w->bodies + i;

		body->position.x += (body->velocity.x * time);
		body->position.y += (body->velocity.y * time);
		body->position.z += (body->velocity.z * time);

		body->velocity.x += (body->acceleration.x * time);
		body->velocity.y += (body->acceleration.y * time);
		body->velocity.z += (body->acceleration.z * time);
	}
	return 1;
}

World sim_let_there_be_light()
{
	World w_space = {
		.max_bodies = BODIES
	};
	world_add_body(&w_space,"sun", YELLOW,
		26715.0f, 100.00f,
		(Vector3) { 0.0f, 0.0f, 0.0f },
		(Vector3) { 0.0f, 0.0f, 0.0f },
		(Vector3) { 0.0f, 0.0f, 0.0f }
	);

	world_add_body(&w_space, "earth",BLUE,
		81.25f, 6.38f,
		(Vector3) { 2000.0f, 0.0f, 0.0f },
		(Vector3) { 0.0f, 0.0f, 3.655f },
		(Vector3) { 0.0f, 0.0f, 0.0f }
	);

	world_add_body(&w_space, "moon", WHITE,
		1.0f, 1.74f,
		(Vector3) { 2200.0f, 0.0f, 0.0f },
		(Vector3) { 0.0f, 0.0f, 4.296f },
		(Vector3) { 0.0f, 0.0f, 0.0f }
	);
	return w_space;
}



#endif
