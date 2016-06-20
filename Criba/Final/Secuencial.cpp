#include "mpi.h"
#include <time.h> 
#include <stdio.h> 
#include <vector>
#include <math.h>  

using namespace std;

#define	Size 48615 //Para sacar 5000 numeros primos

	int 	maxSize;		//Tamaño maximo en el loop secundario
	bool 	BoolNum[Size];		//Arreglo de Validez de Numeros	


	
void invalid_Noprime(int n){
	
	for (int i = 2 ; i <= n; i++ ){		//Loop Principal, verifica si el numero es primo
		if(BoolNum[i]==true) {
			maxSize = Size/i;
			for(int h = 2; h <= maxSize; ++h) //Loop Secundario, invalida los multiplos
				BoolNum[i*h] = false;
			}
		}
}

void criba(){
	//Inicializacion del arreglo 
    	BoolNum[0] = false;
    	BoolNum[1] = false;

    	for(int i = 2; i <= Size; ++i) 
        	BoolNum[i] = true;            	//Poner todos los datos como validos

    	invalid_Noprime(Size);			//Metodo para Invalidar los No_Primos
	
    }
 


float timing(int iteraciones){

	//Init  Variables para medir el tiempo
	double start, end, time, time_P; 
	 
	for(int a =0; a<iteraciones; a++){

		start = MPI_Wtime();		//Toma el tiempo de inicio
		criba();			//Correr el algoritmo
		end = MPI_Wtime();		//Toma el tiempo de finalizacion
		
			
		time = end-start;		//Calcula el tiempo de duracion
		time_P = time_P + time;		//Suma los tiempos en las iteraciones
		}

	time_P = time_P/(iteraciones); 		//Saca el promedio(valor esperado) del algoritmo
	printf("The time was: %f ms\n", time_P*1000 );
	return time_P;
	
	}



int main(int argc,char *argv[]) 
{ 	
	//Init Variables
	int iteraciones=3000;			//Iteraciones para sacar el valor esperado de tiempo
	int cant_prime=0;			//Cantidad de primos encontrados

	float Time1 = timing(iteraciones); 	//Calcula el valor esperado del tiempo que dura el algoritmo
	for(int c=0; c<48615;c++){
		if(BoolNum[c]==true)cant_prime++;	//Cuenta los primos de la lista
	}

	printf("Cantidad de primos %d \n", cant_prime); //Imprime la Cantidad de Primos encontrados

return 0; 
}

