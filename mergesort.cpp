#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <mpi.h>
using namespace std;

void merge(int *a, int *b, int l, int m, int r);
//main function for mearge
void mergeSort(int *a, int *b, int l, int r);
int main(int argc, char** argv)
{

int ArraySize=6;
int *original_array = new int[ArraySize] ;
cout<<"\n\n Done by Maitreyee Paliwal \n\n";


int Process_rank;
int ProcessSize;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &Process_rank);
MPI_Comm_size(MPI_COMM_WORLD, &ProcessSize);
//Print array
if (Process_rank==0)
{
cout << " Array to sort\n ";
for (int c = 0; c <ArraySize; c++)
{
original_array[c] = rand() % ArraySize;
if(c==ArraySize-1){
cout << original_array[c];
}
else{
cout << original_array[c]<<", ";}
}
cout << "\n";
}

int SizeForSub = ArraySize / ProcessSize;

int *sub_array = new int[SizeForSub];
MPI_Scatter(original_array, SizeForSub, MPI_INT, sub_array, SizeForSub, MPI_INT, 0, MPI_COMM_WORLD);

for (int i = 0; i < ProcessSize; i++)
{
cout << "sub array (Sub Parallel Process): " << Process_rank << "\n";
for (int c = 0; c < SizeForSub; c++)
{
if(c==SizeForSub-1){
cout << sub_array[c];
}
else{
cout << sub_array[c]<<", ";
}
}
printf("\n");
break;
}
int *tmp_array = new int[SizeForSub];
mergeSort(sub_array, tmp_array, 0, (SizeForSub - 1));

int *sorted =NULL;
if(Process_rank== 0)
{
sorted = new int[ArraySize];
}
MPI_Gather(sub_array, SizeForSub, MPI_INT, sorted, SizeForSub, MPI_INT, 0,
MPI_COMM_WORLD);

if(Process_rank == 0)
{
int *other_array =new int[ArraySize] ;
mergeSort(sorted, other_array, 0, (ArraySize - 1));

cout<<"The sorted array is:\n";
for(int c = 0; c <ArraySize; c++)
{
if(c==ArraySize-1){
cout << sorted[c];
}
else{
cout << sorted[c]<<", ";
}
}
cout<<"\n\n\n";
free(sorted);
free(other_array);
}
free(original_array);
free(sub_array);
free(tmp_array);

MPI_Barrier(MPI_COMM_WORLD);
MPI_Finalize();
}


void merge(int *a, int *b, int l, int m, int r)
{
int h, i, j, k;
h = l;
i = l;
j = m + 1;
while ((h <= m) && (j <= r))
{
if (a[h] <= a[j])
{
b[i] = a[h];
h++;
}
else
{
b[i] = a[j];
j++;
}
i++;
}
if (m < h)
{
for (k = j; k <= r; k++)
{
b[i] = a[k];
i++;
}
}
else
{
for (k = h; k <= m; k++)
{
b[i] = a[k];
i++;
}
}
for (k = l; k <= r; k++)
{
a[k] = b[k];
}
}

void mergeSort(int *a, int *b, int l, int r)
{
int m;
if (l < r) {
m = (l + r) / 2;
mergeSort(a, b, l, m);
mergeSort(a, b, (m + 1), r);
merge(a, b, l, m, r);
}
}
