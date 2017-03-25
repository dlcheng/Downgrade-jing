#ifndef ALLVAR_H
 #include "allvars.h"
#endif

void init_all();
void jing_simulation_head();

void load_jing_pos();
void load_jing_vel();
void part_jing_pos(long int i, float * pos);
void part_jing_vel(long int i, float * vel);

void free_all();

void out_put_data();
void get_np_now();


void warn_and_end(char *s);
void state(char *s);