#ifndef SIM_C
#define SIM_C

#include "world.h"

#define GRAV_CONSTANT 1.0f

// change the net acceleration of each object
int sim_tick(World *w, double *elapsed_time)
{
	int n_b = w->n_bodies;
	for (int i = 0; i < n_b; i++) {
		Body *body = w->bodies + i;
		// TO DO: compute net force on each body
	}

	return 1;
}




#endif
