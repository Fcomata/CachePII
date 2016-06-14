
#include <time.h> 
#include <stdio.h> 
//#include <dos.h> 


void criba(bool m[], int tam){
    m[0] = false;
    m[1] = false;
    for(int i = 2; i <= tam; ++i) 
        m[i] = true;

    for(int i = 2; i*i <= tam; ++i) {
        if(m[i]) {
            for(int h = 2; i*h <= tam; ++h)
                m[i*h] = false;
        }
    }
}


int main(void) 
{ 
	
	float time_P =0;
	int iteraciones=3000;
	
	for(int a =0; a<=iteraciones; a++){
		clock_t start, end; 
		start = clock(); 

			int tam =48615; //Para sacar 5000 numeros primos
			bool BoolNum[tam] ;
			
			int prim_num=0;

			criba(BoolNum, tam);

		end = clock(); 

		float time = (end-start);
		time_P = time_P + time;
}

time_P = time_P/(iteraciones+1);

printf("The time was: %f\n", time_P); 

return 0; 
}
