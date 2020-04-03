#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "Eurostat_aux_headers.h"

//Must be repeated here:
//Global GSL RNG: global constant variable: continues to exist for whole duration of main
extern gsl_rng * FLAME_GSL_RNG;  /* global GSL random generator */
