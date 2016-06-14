#include <stdio.h> 
	

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

int main(){
	
	int tam =48615; //Para sacar 5000 numeros primos
	bool BoolNum[tam] ;
	
	int prim_num=0;

	criba(BoolNum, tam);
	
	for(int a=0; a<=tam; a++){
		
		if(BoolNum[a]==true){prim_num++;}
		
		}
	
		
		//printf("%4d",prim_num);
		//for(int a=0; a<=tam; a++){if(BoolNum[a]==true){printf("%4d",a);printf("  ");}}
		
	
	}
	



