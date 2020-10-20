#include <stdio.h>    
#include <string.h>   
#include <mpi.h>      
#define MAX 1000


long long bin(int n)
{
    long long binaryNumber = 0;
    int remainder, i = 1, step = 1;

    while (n!=0)
    {
        remainder = n%2;
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}

int main(int argc, char** argv) {
    printf("Done by Maitreyee Paliwal \n\n ");
    int id = -1, numProcesses = -1;
    char sendBuffer[MAX] = {'\0'};
    char recvBuffer[MAX] = {'\0'};
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    if (numProcesses > 1) {
        if ( id == 0 ) {                              
           char res[1000];
            sprintf(sendBuffer, "%03d", bin(id+1));            

            MPI_Send(sendBuffer, strlen(sendBuffer) + 1,MPI_CHAR, id+1, 1,MPI_COMM_WORLD); 

            MPI_Recv(recvBuffer, MAX, MPI_CHAR,  numProcesses-1, 1, MPI_COMM_WORLD, &status);    

            printf("At the end, Process ID %d received %s\n", id, recvBuffer);
        } else {                                     
            MPI_Recv(recvBuffer, MAX, MPI_CHAR, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);   

            printf("At the end, Process ID %d received %s\n", id, recvBuffer);

            sprintf(sendBuffer, "%03d", bin(id+1));

            MPI_Send(sendBuffer, strlen(sendBuffer) + 1, MPI_CHAR, (id+1) % numProcesses, 1, MPI_COMM_WORLD);  
        }
    } else {
        printf("\nRun this program with at least 2 processes\n\n");
    }

    MPI_Finalize();
    return 0;
}
