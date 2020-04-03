#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "Human_aux_headers.h"

//Must be repeated here:
//Global GSL RNG: global constant variable: continues to exist for whole duration of main
extern gsl_rng * FLAME_GSL_RNG;  /* global GSL random generator */


/** \fn state_transition_aux()
 * \brief Function to compute state transition
 * \brief p[4]: probability vector of size 4
 * \brief return: new state of agent
 */
int state_transition_aux(const double * p)
{
	gsl_ran_discrete_t * g;

	//GSL:
	// Given K discrete events with different probabilities P[k], produce a random value k consistent with its probability.

	//1. This function returns a pointer to a structure that contains the lookup table for the discrete random number generator.
 	//gsl_ran_discrete_t * gsl_ran_discrete_preproc (size_t K, const double * P)
 	g = gsl_ran_discrete_preproc(4, p);

	//2. After the preprocessor, above, has been called, you use this function to get the discrete random numbers.
	//size_t gsl_ran_discrete (r,g)
	int state = gsl_ran_discrete(FLAME_GSL_RNG, g);

	//3. De-allocates the lookup table pointed to by g.
	//void gsl_ran_discrete_free (gsl_ran_discrete_t * g)
	gsl_ran_discrete_free(g);

	return state;
}
