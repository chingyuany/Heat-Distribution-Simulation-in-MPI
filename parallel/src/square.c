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

void exchange_ghost_row(int rank, int np, MPI_Status status, float seg[][SIZE], float top_buffer[SIZE], float bottom_buffer[SIZE])
{
    /* do exchange only if there are more than two processors generated*/
    if (np > 1)
    {
        /* neighbouring processors use (send receive) (receive send) pattern to avoid deadlock */
        if (rank == 0)
        {
            MPI_Send(seg[SIZE / np - 1], SIZE, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(bottom_buffer, SIZE, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD, &status);
        }
        else if (rank != np - 1)
        { /* receive from the previous processor first */
            MPI_Recv(top_buffer, SIZE, MPI_FLOAT, rank - 1, 0, MPI_COMM_WORLD, &status);
            MPI_Send(seg[0], SIZE, MPI_FLOAT, rank - 1, 0, MPI_COMM_WORLD);

            MPI_Send(seg[SIZE / np - 1], SIZE, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(bottom_buffer, SIZE, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD, &status);
        }
        else
        {
            MPI_Recv(top_buffer, SIZE, MPI_FLOAT, rank - 1, 0, MPI_COMM_WORLD, &status);
            MPI_Send(seg[0], SIZE, MPI_FLOAT, rank - 1, 0, MPI_COMM_WORLD);
        }
    }
}

void copy_new_to_old(int rank, int np, float new[][SIZE], float old[][SIZE])
{
    int row_cnt = SIZE / np;
    if (rank == np - 1)
    {
        row_cnt += SIZE % np; // the last processor should take the rest of lines of the original square
        memcpy(old, new, sizeof(float) * row_cnt * SIZE);
    }
    else
    {
        memcpy(old, new, sizeof(float) * row_cnt * SIZE);
    }
}

void calculate_new(int rank, int np, float new[][SIZE], float old[][SIZE], float top_buffer[SIZE], float bottom_buffer[SIZE])
{
    int row_cnt = SIZE / np;
    /* if only one processor, do as the sequential program */
    if (np == 1)
    {
        /* ignore the four edges */
        for (int x = 1; x < row_cnt - 1; x++)
        {
            for (int y = 1; y < SIZE - 1; y++)
            {
                new[x][y] = (old[x][y - 1] + old[x][y + 1] + old[x - 1][y] + old[x + 1][y]) / 4;
            }
        }
        return;
    }
    /* more than one processor generated */
    if (rank == 0)
    {
        /* ignore the first line, the left side and the right side */
        for (int x = 1; x < row_cnt; x++)
        {
            for (int y = 1; y < SIZE - 1; y++)
            {
                if (x == row_cnt - 1)
                {
                    new[x][y] = (old[x][y - 1] + old[x][y + 1] + old[x - 1][y] + bottom_buffer[y]) / 4;
                }
                else
                {
                    new[x][y] = (old[x][y - 1] + old[x][y + 1] + old[x - 1][y] + old[x + 1][y]) / 4;
                }
            }
        }
    }
    else if (rank == np - 1)
    {
        row_cnt += SIZE % np; // the last processor should take the rest of lines of the original square
        /* ignore the last line, the left side and the right side */
        for (int x = 0; x < row_cnt - 1; x++)
        {
            for (int y = 1; y < SIZE - 1; y++)
            {
                if (x == 0)
                {
                    new[x][y] = (old[x][y - 1] + old[x][y + 1] + top_buffer[y] + old[x + 1][y]) / 4;
                }
                else
                {
                    new[x][y] = (old[x][y - 1] + old[x][y + 1] + old[x - 1][y] + old[x + 1][y]) / 4;
                }
            }
        }
    }
    else
    {
        row_cnt = SIZE / np;
        /* only ignore the left side and the right side */
        for (int x = 0; x < row_cnt; x++)
        {
            for (int y = 1; y < SIZE - 1; y++)
            {
                if (row_cnt == 1) // if only one line in the segment, use top_buffer and bottom_buffer
                {
                    new[x][y] = (old[x][y - 1] + old[x][y + 1] + top_buffer[y] + bottom_buffer[y]) / 4;
                }
                else
                {
                    if (x == 0)
                    {
                        new[x][y] = (old[x][y - 1] + old[x][y + 1] + top_buffer[y] + old[x + 1][y]) / 4;
                    }
                    else if (x == row_cnt - 1)
                    {
                        new[x][y] = (old[x][y - 1] + old[x][y + 1] + old[x - 1][y] + bottom_buffer[y]) / 4;
                    }
                    else
                    {
                        new[x][y] = (old[x][y - 1] + old[x][y + 1] + old[x - 1][y] + old[x + 1][y]) / 4;
                    }
                }
            }
        }
    }
}

