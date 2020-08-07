#ifndef _SQUARE_H
#define _SQUARE_H

#include "common.h"

void init_square(float s[][SIZE]);
void set_fire_place(float s[][SIZE]);
void print_square(float s[][SIZE]); // print the numerical result for testing
void copy_new_to_old(float new[][SIZE], float old[][SIZE]);
void calculate_new(float new[][SIZE], float old[][SIZE]);

#endif

