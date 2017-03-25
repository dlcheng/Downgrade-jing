#ifndef ALLVAR_H
#define ALLVAR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>

typedef struct head_jing HEAD_JING;

struct head_jing
{
  long int np;
  long int x1;
  float x2[6];
};

/* Simulation information */
extern long int np;                    /* the total number of orginal simulation particles */
extern long int np_now;                /* the total number of simulation after downgrading */

extern gsl_rng *r;                     /* the random number generator */
extern int seed;                       /* seed of the generator */
extern double saved_frac;              /* the preserved fraction of particles */

extern HEAD_JING head;                 /* the head of simulation file */

/* Particle information */
extern float * j_pos;                  /* the position info of Jing simulation */
extern float * j_vel;                  /* the velocity info of Jing simulation */
extern char  * reader_pos;             /* char arrays of pos */
extern char  * reader_vel;             /* char arrays of vel */

#endif
