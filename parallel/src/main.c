#include "../include/square.h"
#include "../include/printcolors.h"

int main(int argc, char *argv[])
{
    int rank;
    int np;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    float square[SIZE][SIZE];
    init_square(square);
    set_fire_place(square);

    /* sendcounts/recvcounts and displs for scatterv and getherv */
    int *sendcnts = malloc(sizeof(int) * np);
    int *recvcnts = sendcnts;
    int *displs = malloc(sizeof(int) * np);
    /* initialize the sendcounts and disples */
    for (int r = 0; r < np; r++)
    {
        if (r == np - 1 && SIZE % np != 0)
        {
            sendcnts[r] = SIZE * (SIZE / np + SIZE % np);
        }
        else
        {
            sendcnts[r] = SIZE * (SIZE / np);
        }

        if (r == 0)
        {
            displs[r] = 0;
        }
        else
        {
            displs[r] = displs[r - 1] + sendcnts[r - 1];
        }
    }

    /* new and old segment of square */
    float(*new_segment)[SIZE];
    float(*old_segment)[SIZE];
    /* initialize the segment for each processor */
    new_segment = malloc(sizeof(float) * sendcnts[rank]);
    old_segment = malloc(sizeof(float) * sendcnts[rank]);

    /* scatter the square to slaves */
    MPI_Scatterv(square, sendcnts, displs, MPI_FLOAT, new_segment, recvcnts[rank], MPI_FLOAT, 0, MPI_COMM_WORLD);

    /* ghost buffer initialization */
    float ghost_top_buffer[SIZE] = {0};
    float ghost_bottom_buffer[SIZE] = {0};

    /* the main iteration loop */
    for (int loop = 0; loop < LOOP_TIME; loop++)
    {
        exchange_ghost_row(rank, np, status, new_segment, ghost_top_buffer, ghost_bottom_buffer);
        // wait for all ghost received by slaves
        MPI_Barrier(MPI_COMM_WORLD);
        copy_new_to_old(rank, np, new_segment, old_segment);
        calculate_new(rank, np, new_segment, old_segment, ghost_top_buffer, ghost_bottom_buffer);
    }

    /* gather all segments to the master */
    MPI_Gatherv(new_segment, sendcnts[rank], MPI_FLOAT, square, recvcnts, displs, MPI_FLOAT, 0, MPI_COMM_WORLD);

    /* free memory */
    free(sendcnts);
    sendcnts = NULL;
    recvcnts = NULL;
    free(displs);
    displs = NULL;
    free(new_segment);
    new_segment = NULL;
    free(old_segment);
    old_segment = NULL;

    /* generate graphical output */
    if (rank == 0)
    {
        print_colors(square);
    }

    MPI_Finalize();
    return 0;
}