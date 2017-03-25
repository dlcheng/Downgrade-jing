#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>

#include "allvars.h"

/* Simulation information */
long int np;                    /* the total number of orginal simulation particles */
long int np_now;                /* the total number of simulation after downgrading */

gsl_rng *r;                     /* the random number generator */
int seed;                       /* seed of the generator */
double saved_frac;

HEAD_JING head;                 /* the head of simulation file */

/* Particle information */
float * j_pos;                  /* the position info of Jing simulation */
float * j_vel;                  /* the velocity info of Jing simulation */
char  * reader_pos;             /* char arrays of pos */
char  * reader_vel;             /* char arrays of vel */

