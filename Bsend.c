
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
            int buffer_attached_size = MPI_BSEND_OVERHEAD + sizeof(int);
            int buffer_sent;
            scanf("%d", &buffer_sent);
            char* buffer_attached = (char*)malloc(buffer_attached_size);
            MPI_Buffer_attach(buffer_attached, buffer_attached_size);
            printf("\n[MPI process %d] I send value %d.\n", my_rank, buffer_sent);
            MPI_Bsend(&buffer_sent, 1, MPI_INT, RECEIVER, 0, MPI_COMM_WORLD);
 
            MPI_Buffer_detach(&buffer_attached, &buffer_attached_size);
            free(buffer_attached);
            break;
        }
        case RECEIVER:
        {
            // Receive the message and print it.
            int received;
            MPI_Recv(&received, 1, MPI_INT, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("\n[MPI process %d] I received value: %d.\n", my_rank, received);
            break;
        }
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
