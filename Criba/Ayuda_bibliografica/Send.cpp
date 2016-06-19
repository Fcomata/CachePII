#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define NUM_THREADS 4
#define NUM_DATA 1000

int main(int argc, char *argv[]) {
   int *list;
   int numprocs, rank, namelen, i, n;
   int chunksize,offset;
   char processor_name[MPI_MAX_PROCESSOR_NAME];

   n= NUM_DATA * NUM_DATA;

   MPI_Status stat;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Get_processor_name(processor_name, &namelen);

   //note you'll need to handle n%NUM_THREADS !=0, but i'm ignoring that for now
   chunksize = n / NUM_THREADS; 

   if (rank == 0) {
      //Think of this as a master process
      //Do your initialization in this process
      list = malloc(n*sizeof(int));

      for(i = 0 ; i < n; i++)
      {
         list[i] = rand() % 1000;
      }

      // Once you're ready, send each slave process a chunk to work on
      offset = chunksize;
      for(i = 1; i < numprocs; i++) {
         MPI_Send(&list[offset], chunksize, MPI_INT, i, 0, MPI_COMM_WORLD);
         offset += chunksize;
      }

     // search(list, 0, chunksize);

      //If you need some sort of response back from the slaves, do a recv loop here
   } else {

      // If you're not the master, you're a slave process, so wait to receive data

      list = malloc(chunksize*sizeof(int));  
      MPI_Recv(list, chunksize, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);

      // Now you can do work on your portion
     // search(list, 0, chunksize);

      //If you need to send something back to the master, do it here.
   }

   MPI_Finalize();
}
