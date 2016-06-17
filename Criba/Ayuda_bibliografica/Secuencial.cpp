#include "mpi.h"
#include <time.h> 
#include <stdio.h> 
#include <vector>
#include <omp.h>
#include <math.h> 

using namespace std;


int tam =48615; //Para sacar 5000 numeros primos
int maxtam, TamRaiz;

void criba(bool m[], int tam){
    m[0] = false;
    m[1] = false;
 

    for(int i = 2; i <= tam; ++i) 
        m[i] = true;

  TamRaiz = sqrt(tam);

    for(int i = 2; i <= TamRaiz; ++i) {
        if(m[i]) {
	    maxtam = tam/i;
            for(int h = 2; h <= maxtam; ++h)

                m[i*h] = false;
        }

	
    }
 
}

float timing(int iteraciones){
	

	bool BoolNum[tam] ;
	int prim_num=0;
	double start, end, time, time_P; 
	 
	for(int a =0; a<iteraciones; a++){

		start = omp_get_wtime();
			criba(BoolNum, tam);
		end = omp_get_wtime();
		

		float time = (end-start);
		time = end-start;
		time_P = time_P + time;
		}

	time_P = time_P/(iteraciones); 
	printf("The time was: %f ms\n", time_P*1000 );
	return time_P;
	
	}


int main(void) 
{ 
	int iteraciones=3000;
	float Time1 = timing(iteraciones);

return 0; 
}
