# include <math.h>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main ( int argc, char *argv[] );
int prime_number ( int n, int id, int p );

int main ( int argc, char *argv[] )
{
  int i,id,ierr,n,n_factor,n_hi,n_lo,p,primes,primes_part;
  double wtime;

 
  n_hi = 48615;
  n_factor = 2;

  ierr = MPI_Init ( &argc, &argv );
  ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
  ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );

 
  
 	wtime = MPI_Wtime ( );
  	n = n_hi;

    ierr = MPI_Bcast ( &n, 1, MPI_INT, 0, MPI_COMM_WORLD );
    primes_part = prime_number ( n, id, p );
    ierr = MPI_Reduce ( &primes_part, &primes, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );
    
	if(id==0) printf ( "  %8d  %8d  %14f\n", n, primes, wtime );


  ierr = MPI_Finalize ( );
  wtime = MPI_Wtime ( ) - wtime ; 
  printf("Tiempo: %f \n", wtime);

	
  return 0;


	
}

int prime_number ( int n, int id, int p )

{
  int i;
  int j;
  int prime;
  int total;

  total = 0;

  for ( i = 2 + id; i <= n; i = i + p )
  {
    prime = 1;
    for ( j = 2; j < i; j++ )
    {
      if ( ( i % j ) == 0 )
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }
  return total;
}
