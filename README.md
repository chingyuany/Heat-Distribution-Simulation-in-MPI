# Heat-Distribution-Simulation-in-MPI
The temperature of the interior of an area will depend on the temperatures around it. Consider
a square area that has known temperatures along each of its edges, and a single heat source at
one location.
This program is to compute distribution of heat in a region over time given a fixed heat source.


Compiling instructions:
    Sequential program:
        1. cd ./sequential
        2. issue "make" to build the sequential program
        3. issue "./app" to run the program, you can check the graphical output in the "output" directory. 
        4. issue "make clean" to delete the object files and the executable program
    Parallel program:
        1. cd ./parallel
        2. issue "make" to build the parallel program
        3. issue "mpirun -np [n] app" to run the program, you can check the graphical output in the "output" directory. 
        4. issue "make clean" to delete the object files and the executable program

Assumption:
    1. The temperature of the edges is fixed at 20 degrees Celsius.
    2. Size of a mesh sets to 1000 by 1000.
    3. Number of Iteration set to 50000. 
    4. A fireplace that is 40% of the mesh size and placed on the second row. 
    5. Fireplace temperature set at 300 degrees Celsius.
    6. You can modify those parameters in "./include/common.h"
