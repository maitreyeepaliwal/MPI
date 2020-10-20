#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;
int main(int argc, char** argv)
{
        cout<<"Done by Maitreyee Paliwal \n\n\n";
        double t1, t2; 
        t1 = MPI_Wtime();
	int i,j,k,p,a[100],b[25],myrank,x,y,interval,sum = 0,c[4];
        float res, finalres;

	for(i=0;i<100;i++)
		a[i] = i+1;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	MPI_Scatter(a,25,MPI_INT,b,25,MPI_INT,0,MPI_COMM_WORLD);

	res = 0;
	for(i=0;i<25;i++)
		res+=b[i];

        MPI_Reduce ( &res, &finalres, 1, MPI_FLOAT, MPI_SUM , 0, MPI_COMM_WORLD);

     if ( myrank == 0 )
     {
        double out;
        cout << "Sum = " << finalres << endl << endl;
        out = finalres/100;
        cout<< "Average = "<< out << endl;
        t2 = MPI_Wtime(); 
        cout<<"\nElapsed Time = "<<t2-t1<<"\n";
     }
 
	MPI_Finalize();
	return 0;
}
