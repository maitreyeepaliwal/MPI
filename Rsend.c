#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    printf("Done by Maitreyee Paliwal \n\n");
    MPI_Init(&argc, &argv);
     int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 2)
    {
        printf("This application is meant to be run with 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    enum role_ranks { SENDER, RECEIVER };
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    switch(my_rank)
    {
        case SENDER:
        {
            printf("MPI process ID %d hits the barrier to wait for the matching MPI_Recv to be posted.\n\n", my_rank);
            MPI_Barrier(MPI_COMM_WORLD);
            printf("MPI_Rsend can now be issued.\n\n");
 
            int buffer_sent = 2401;
            printf("MPI process ID %d sends value %d.\n\n", my_rank, buffer_sent);
            MPI_Rsend(&buffer_sent, 1, MPI_INT, RECEIVER, 0, MPI_COMM_WORLD);
            break;
        }
        case RECEIVER:
        {
            int received;
            MPI_Request request;
            MPI_Irecv(&received, 1, MPI_INT, SENDER, 0, MPI_COMM_WORLD, &request);
 
            printf("MPI process ID %d issued the MPI_Irecv, moved on and hit the barrier.\n\n", my_rank);
            MPI_Barrier(MPI_COMM_WORLD);
 
            // Wait for the underlying MPI_Recv to complete.
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            printf("MPI process ID %d receives value %d.\n\n", my_rank, received);
            break;
        }
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
