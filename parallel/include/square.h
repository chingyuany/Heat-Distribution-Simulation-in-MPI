#ifndef _SQUARE_H
#define _SQUARE_H

#include "common.h"

void init_square(float s[][SIZE]);
void set_fire_place(float s[][SIZE]);
void print_square(float s[][SIZE]); // print the numerical result for testing
void exchange_ghost_row(int rank, int np, MPI_Status status, float seg[][SIZE], float top_buffer[SIZE], float bottom_buffer[SIZE]);
void copy_new_to_old(int rank, int np, float new_seg[][SIZE], float old_seg[][SIZE]);
void calculate_new(int rank, int np, float new_seg[][SIZE], float old_seg[][SIZE], float top_buffer[SIZE], float bottom_buffer[SIZE]);

#endif
