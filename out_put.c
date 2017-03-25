#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "allvars.h"
#include "proto.h"
#include "define.h"

void out_put_data()
{
  long int i_start;
  unsigned int block_size;
  unsigned int np_loc;                          /* the actual number of particles within a block */
  unsigned int np_block_max = 178956970;        /* the max particle numer in a block */
  long int np_left;                             

  char file_name1[500];                         /* for pos */
  char file_name2[500];                         /* for vel */
  FILE *fp_pos;
  FILE *fp_vel;

  float pos[3];
  float vel[3];

  sprintf(file_name1, "%s%s%04d%s%04d", OUTPUT_FOLDER, "pos", SNAPSHOT, ".", CUR_STEP);
  sprintf(file_name2, "%s%s%04d%s%04d", OUTPUT_FOLDER, "vel", SNAPSHOT, ".", CUR_STEP);  

  if((fp_pos = fopen(file_name1, "wb+")) == NULL)    
    {
	   printf("Fail to open output file %s\n", file_name1);
	   exit(0);
	  }
  
  if((fp_vel = fopen(file_name2, "wb+")) == NULL)    
    {
     printf("Fail to open output file %s\n", file_name2);
     exit(0);
    }
  
  get_np_now();

  printf("Output particle numer = %ld\n", np_now);

  head.np = np_now;

/* make the head  */
  block_size = sizeof(head);
  fwrite(&block_size, sizeof(block_size), 1, fp_pos);
  fwrite(&head, sizeof(head), 1, fp_pos);
  fwrite(&block_size, sizeof(block_size), 1, fp_pos);

  fwrite(&block_size, sizeof(block_size), 1, fp_vel);
  fwrite(&head, sizeof(head), 1, fp_vel);
  fwrite(&block_size, sizeof(block_size), 1, fp_vel);

  np_left = np_now;
  i_start = 0;       

  while(np_left != 0)
    {
    if(np_left > np_block_max)
      {
       block_size = 3 * sizeof(float) * np_block_max;
       np_loc = np_block_max;
       fwrite(&block_size, sizeof(block_size), 1, fp_pos);
       fwrite(&block_size, sizeof(block_size), 1, fp_vel);

       while(np_loc != 0)
        {
        if(gsl_rng_uniform(r) < saved_frac)
          {
          part_jing_pos(i_start, pos);
          part_jing_vel(i_start, vel);
          fwrite(pos, 3*sizeof(float), 1, fp_pos);
          fwrite(vel, 3*sizeof(float), 1, fp_vel);
          np_loc--;
          }
        i_start++;
        }

       fwrite(&block_size, sizeof(block_size), 1, fp_pos);
       fwrite(&block_size, sizeof(block_size), 1, fp_vel);
       np_left -= np_block_max;
      }
    else
      {
       block_size = 3 * sizeof(float) * np_left;
       np_loc = np_left;
       fwrite(&block_size, sizeof(block_size), 1, fp_pos);
       fwrite(&block_size, sizeof(block_size), 1, fp_vel);

       while(np_loc != 0)
        {
        if(gsl_rng_uniform(r) < saved_frac)
          {
          part_jing_pos(i_start, pos);
          part_jing_vel(i_start, vel);
          fwrite(pos, 3*sizeof(float), 1, fp_pos);
          fwrite(vel, 3*sizeof(float), 1, fp_vel);
          np_loc--;
          }
        i_start++;
        }
       
       fwrite(&block_size, sizeof(block_size), 1, fp_pos);
       fwrite(&block_size, sizeof(block_size), 1, fp_vel);
       np_left -= np_left;
      }       /* this is the last block */
    }

  fclose(fp_pos);	
  fclose(fp_vel);
  
}    /* end write file */	


void get_np_now()
{
  long int i;
  gsl_rng_set(r, seed);
  double temp; 
  for(i=0; i<np; i++)
    {
      temp = gsl_rng_uniform(r);
     if(temp < saved_frac)
        np_now++;
    } 

  gsl_rng_set(r, seed);        /* set the rng to default state */
}   /* end get_np_now */