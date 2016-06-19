#include "mpi.h"
#include <time.h> 
#include <stdio.h> 
#include <vector>
#include <math.h> 

using namespace std;

#define	Size 48615 //Para sacar 5000 numeros primos

	int 	maxSize,  	//Tamaño maximo en el loop secundario
		id,		//Identificacion del CPU
		p,		//Numero de Procesos
		global_count,
		ierr;		//MPI ERR

	bool 	BoolNum[Size];	//Arreglo de Validez de Numeros	
	
	

void invalid_Noprime(int n){

	
	int chunks = sqrt(Size)/4;

	for (int i = 2 + id*chunks; i <= (id+1)*chunks ; i = i+1){ //Loop Principal, verifica si el numero es primo
		if(BoolNum[i]==true) {
			maxSize = Size/i;
			for(int h = 2; h <= maxSize; ++h){ //Loop Secundario, invalida los multiplos
				BoolNum[i*h]= false;
				int multiple=i*h;
				MPI_Bcast (&multiple, 1, MPI_INT, 0, MPI_COMM_WORLD);             
		                }
		
			}

		}
MPI_Reduce(BoolNum, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

}

void criba(){

   	 //Inicializacion del arreglo  
	 BoolNum[0] = false;
	 BoolNum[1] = false;
	 for(int i = 2; i <= Size; ++i){
		BoolNum[i] = true;	//Poner todos los datos como validos
		}
	
	 //Metodo para Invalidar los No_Primos
	 invalid_Noprime(Size);
	
	    }
 


float timing(int iteraciones){
	
	//Init  Variables para medir el tiempo
	double start, end, time, time_P;  
	 
	for(int a =0; a<iteraciones; a++){
		if(id==0)
			start = MPI_Wtime(); 		//Toma el tiempo de inicio

		criba();				//Correr el algoritmo

		if(id==0){
			end = MPI_Wtime();		//Toma el tiempo de finalizacion
			time = end-start;		//Calcula el tiempo de duracion
			time_P = time_P + time;		//Suma los tiempos en las iteraciones	
		}
	}

	if(id==0){
		time_P = time_P/(iteraciones); 		//Saca el promedio(valor esperado) del algoritmo
		printf("The time was: %f ms\n", time_P*1000 );
	}

	return time_P;
	
	}



int main(int argc,char *argv[]) 
{ 
	
	//Init Variables
	int iteraciones=3000; 				//Iteraciones para sacar el valor esperado de tiempo
	int cant_primes=0; 				//Cantidad de primos encontrados

	//Init MPI
	ierr = MPI_Init ( &argc, &argv );
  	ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p ); 	//Cantidad de Procesos P
  	ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );	//IDs de CPUs

	if(id==0){printf("#P: %d \n", p);}

	float Time1 = timing(iteraciones);		//Calcula el valor esperado del tiempo que dura el algoritmo
	
	if(id==0){
	for(int c=0; c<48615;c++){
		if(BoolNum[c]==true)cant_primes++;	//Cuenta los primos de la lista
		}

	printf("Cantidad de primos %d \n", cant_primes); //Imprime la Cantidad de Primos encontrados
	}

	//Fin MPI
	ierr = MPI_Finalize ( );

return 0; 
}

