#include "../include/square.h"

void init_square(float s[][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            s[i][j] = INIT_TEMPERATURE;
        }
    }
}

void set_fire_place(float s[][SIZE])
{
    int num_fire_point = SIZE * FIRE_POINT_RANGE;
    int left_fire_point = (SIZE - num_fire_point) / 2;
    int righr_fire_point = left_fire_point + num_fire_point - 1;
    /* set fire point on the center of the first line */
    for (int i = left_fire_point; i <= righr_fire_point; i++)
    {
        s[0][i] = FIRE_TEMPERATURE;
    }
}

void print_square(float s[][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%.3f ", s[i][j]);
        }
        printf("\n");
    }
}

void copy_new_to_old(float new[][SIZE], float old[][SIZE])
{
    memcpy(old, new, sizeof(float) * SIZE * SIZE);
}

void calculate_new(float new[][SIZE], float old[][SIZE])
{
    /* ignore four edges */
    for (int x = 1; x < SIZE - 1; x++)
    {
        for (int y = 1; y < SIZE - 1; y++)
        {
            new[x][y] = (old[x][y - 1] + old[x][y + 1] + old[x - 1][y] + old[x + 1][y]) / 4;
        }
    }
}