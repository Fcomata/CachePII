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
		rootSize;

	bool 	BoolNum[Size];
  	double  wtime;

	
void invalid_Noprime(int n){
	
for (int i = 2 ; i <= n; i++ ){
        if(BoolNum[i]) {
		maxSize = Size/n;
        	for(int h = 2; h <= maxSize; ++h)
        		BoolNum[i*h] = false;
		}
	}
}

void criba(){

    BoolNum[0] = false;
    BoolNum[1] = false;
    for(int i = 2; i <= Size; ++i) 
        BoolNum[i] = true;

    rootSize = sqrt(Size);
    invalid_Noprime(Size);
	
    }
 


float timing(int iteraciones){
	
	double start, end, time, time_P; 
	 
	for(int a =0; a<iteraciones; a++){

		start = omp_get_wtime();
		criba();
		end = omp_get_wtime();
		
		float time = (end-start);
		time = end-start;
		time_P = time_P + time;
		}

	time_P = time_P/(iteraciones); 
	printf("The time was: %f ms\n", time_P*1000 );
	return time_P;
	
	}



int main(int argc,char *argv[]) 
{ 
	int iteraciones=3000;

	float Time1 = timing(iteraciones);


return 0; 
}

