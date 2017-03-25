#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "allvars.h"
#include "proto.h"
#include "define.h"

void init_all()
{
/* load postion and velocity files */  
  r = gsl_rng_alloc(gsl_rng_taus);
  seed = SEED;
  saved_frac = SAVED_FAC;
  np_now = 0;

/* load the head */
  jing_simulation_head();
  np = head.np;

/* load the full particle data */  
  load_jing_pos();
  load_jing_vel();

}    /* end init_all */

void jing_simulation_head()
{
  FILE *fp;

  char file_test[256];
  
  if(FILE_NUM == 1) 
    sprintf(file_test, "%s%s%04d%s%04d", INPUT_FOLDER, "/pos", SNAPSHOT, ".", CUR_STEP);
  else
    sprintf(file_test, "%s%s%04d%s%04d%s%02d", INPUT_FOLDER, "/pos", SNAPSHOT, ".", CUR_STEP,".",1);
  
  fp = fopen(file_test, "rb");
  rewind(fp);
  fseek(fp, sizeof(int), SEEK_SET);
  fread(&head, sizeof(head), 1, fp);                   /* get file head */
  fclose(fp);

}  /* end load_jing_simulation_info */