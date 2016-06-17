# include <cstdlib>
# include <ctime>
# include <iomanip>
# include <iostream>
# include <mpi.h>
#include <time.h> 
#include <stdio.h> 
#include <vector>
#include <math.h> 
#include <omp.h> 

using namespace std;


  int tam =48615; //Para sacar 5000 numeros primos
  int maxtam, TamRaiz;
  int id;
  int ierr;
  int p;
  double wtime, promedio;
  int iteraciones=3000;

void criba(bool m[], int tam, int id){
    m[0] = false;
    m[1] = false;
 

    for(int i = 2; i <= tam; ++i) 
	m[i] = true;
	TamRaiz = sqrt(tam);


	for(int i = 2; i <= TamRaiz; ++i){
		if(m[i]){
			maxtam = tam/i;
		    	for(int h = 2; h <= maxtam; ++h)
		        	m[i*h] = false;
        		}		
    	}
 
}


float timing(int iteraciones, int id){
	

	bool BoolNum[tam] ;
	int prim_num=0;
	double start, end, time, time_P; 
	 
	for(int a =0; a<iteraciones; a++){

	    wtime = MPI_Wtime ( );
	  
	    criba(BoolNum, tam, 0);

	    wtime = MPI_Wtime ( ) - wtime;
	    promedio = promedio + wtime;
	  			
		}

	promedio = promedio/(iteraciones); 
	return promedio;
	
	
	}


int main(int argc, char** argv) {
  // Initialize the MPI environment
    MPI_Init(NULL, NULL);

//  Get the number of processes.
//
  ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
  cout << " #Procesos = " << p << " .\n";
//
//  Get the individual process ID.
//
  ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );
  cout << " #ID = " << id << " .\n";
//
//  Every process prints a hello.
//
   int dest = 0;         /* define the process that computes the final result */
   int tag = 123; 
   MPI_Status status;
   int source,i;
   double result;
   double my_result = timing(iteraciones, id);

if(id == 0) {
        result = my_result;
        for (i=1;i<p;i++) {
          source = i;           /* MPI process number range is [0,p-1] */
          MPI_Recv(&my_result, 1, MPI_REAL, source, tag,
                        MPI_COMM_WORLD, &status);
          result += my_result;
        }
        printf("The result =%f\n",result);
      }
      else
        MPI_Send(&my_result, 1, MPI_REAL, dest, tag,
                      MPI_COMM_WORLD);      /* send my_result to intended dest.
                      */
      MPI_Finalize();                       /* let MPI finish up ... */


//
//  Process 0 says goodbye.
//
if(id==0)
  cout << "  Elapsed wall clock time = " << wtime*1000 << " ms.\n";


	


	

return 0; 
}
