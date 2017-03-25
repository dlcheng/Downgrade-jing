#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "allvars.h"
#include "proto.h"
#include "define.h"

void free_all()
{  
  free(reader_pos);
  free(reader_vel);	
}   /* end free_all */	
