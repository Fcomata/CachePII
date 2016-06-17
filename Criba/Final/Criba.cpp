#include "mpi.h"
#include <time.h> 
#include <stdio.h> 
#include <vector>
#include <omp.h>
#include <math.h> 

using namespace std;

#define	Size 48615 //Para sacar 5000 numeros primos

	int 	 
		maxSize, 
		rootSize,
		id,
		p,	
		ierr;

	bool 	BoolNum[Size];
  	double  wtime;

	
void invalid_Noprime(int n, int id, int p){
	
ierr = MPI_Bcast ( BoolNum, 1, MPI_INT, 0, MPI_COMM_WORLD );

for (int i = 2 + id; i <= n; i = i + p ){
        if(BoolNum[i]) {
		maxSize = Size/n;
        	for(int h = 2; h <= maxSize; ++h)
        		BoolNum[i*h]= false;

		}
	}
}

void criba(){

    BoolNum[0] = false;
    BoolNum[1] = false;
    for(int i = 2; i <= Size; ++i){
        BoolNum[i] = true;
	}

    rootSize = sqrt(Size);
    invalid_Noprime(Size,id,p);
	
    }
 


float timing(int iteraciones){
	
	double start, end, time, time_P; 
	 
	for(int a =0; a<iteraciones; a++){
		if(id==0)
			start = omp_get_wtime();

		criba();

		if(id==0){
			end = omp_get_wtime();
		
			float time = (end-start);
			time = end-start;
			time_P = time_P + time;
		}
	}

	if(id==0){
		time_P = time_P/(iteraciones); 
		printf("The time was: %f ms\n", time_P*1000 );
	}
	return time_P;
	
	}



int main(int argc,char *argv[]) 
{ 
	int iteraciones=3000;
	ierr = MPI_Init ( &argc, &argv );
  	ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
	//printf("#P: %d \n", p);
  	ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );
	float Time1 = timing(iteraciones);
	ierr = MPI_Finalize ( );


return 0; 
}

