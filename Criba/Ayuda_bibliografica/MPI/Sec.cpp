# include <math.h>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main ( int argc, char *argv[] );
int prime_number ( int n);

int main ( int argc, char *argv[] )
{
  int i,id,ierr,n,n_factor,n_hi,n_lo,p,primes,primes_part;
  double wtime;

  n_lo = 1;
  n_hi = 48615;
  n_factor = 2;

 
 	wtime = MPI_Wtime ( );
  	n = n_lo;

  while ( n <= n_hi )
  {
    primes_part = prime_number ( n );
    n = n * n_factor;
  }

  wtime = MPI_Wtime ( ) - wtime ; 
  printf("Tiempo: %f", wtime);

  return 0;


	
}

int prime_number ( int n)

{
  int i;
  int j;
  int prime;
  int total;

  total = 0;

  for ( i = 2 ; i <= n; i++ )
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
