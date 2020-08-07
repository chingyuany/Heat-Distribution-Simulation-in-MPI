#include "../include/square.h"
#include "../include/printcolors.h"

int main()
{
    float new_square[SIZE][SIZE];
    float old_square[SIZE][SIZE];
    init_square(new_square);
    set_fire_place(new_square);
    for (int i = 0; i < LOOP_TIME; i++)
    {
        copy_new_to_old(new_square, old_square);
        calculate_new(new_square, old_square);
    }
    print_colors(new_square);
    return 0;
}