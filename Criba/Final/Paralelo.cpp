//      Sieve of Eratosthenes
// version 1
// tomado de 
// PARALLEL PROGRAMMING in C with MPI and OpenMP
// Michael J. Quinn
// Ed. Mc Graw Hill
// capitulo 5
//
                                                                                                                    
                                                                                                                         
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[ ]){
	int 	count;          //Local prime count
	double 	elapsed_time;   //Parallel execution time
	int 	first;        	//Index of first multiple
	int 	global_count;	//Global prime count
	int 	high_value; 	//Highest value on this proc
	int 	i;
	int 	id;             //Process ID number
	int 	index;          //Index of current prime
	int 	low_value;      //Lowest value on this proc
	char 	*marked;        //Portion of 2, <85>, 'n'
	int 	n;              //Sieving from 2, <85>, 'n'
	int 	p;              //Number of processes
	int 	proc0_size;     //Size ofproc 0's subarray
	int 	prime;          //Current prime
	int 	size;           //Elements in 'marked'

	MPI_Init(&argc, &argv);    
	MPI_Comm_rank (MPI_COMM_WORLD, &id);
	MPI_Comm_size (MPI_COMM_WORLD, &p);
	
	MPI_Barrier (MPI_COMM_WORLD);
	elapsed_time = - MPI_Wtime( );                                                                                                                     

	n = 48615;       
        prime = 2;                                                                                                                 
	low_value  = 2 + id*n/p;
	high_value = 2+ ((id+1)*n/p -1);
	size       = high_value-low_value+1; 
        proc0_size = (n-1)/p;

 	marked = (char *) malloc(size*sizeof(char));                                                                                                                         
                                                                                                              
	//inicialize datablock
	for (i =0; i < size; i++) marked[i]=0;

	if (id==0) index = 0;


	

	while (prime * prime <=n){

		if (prime * prime > low_value)	first = prime * prime - low_value;

		else{
			if (!(low_value % prime)) first = 0;

			else first = prime - (low_value % prime);
		}
		
		for (i = first; i < size; i+=prime) marked[i]=1;


		if(id==0){
			while (marked[++index]);
			prime = index+2;
		}

        MPI_Bcast (&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}
	
	count = 0;

	for (i = 0;i < size; i++)
		if (marked [i]==0){count++;}
		
	MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	elapsed_time +=  MPI_Wtime();
	                                                                                                                         
	if(id==0){
		printf ("Hay %d primos menores o iguales a %d\n"		, global_count, n);
		printf ("\nTotal tiempo transcurrido: %10.6f segundos\n", elapsed_time);
	}

	MPI_Finalize();
	return 0;
}
