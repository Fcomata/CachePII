
	int tam =1 000 000;
	bool [tam] BoolNum;

void main(){
	
	int prim_num=0;
	
	
	criba(BoolNum, tam);
	
	for(int a=0; a<=tam; a++){
		
		if(BoolNum[a]==true){prim_num++;}
		
		}
		
		cout<<prim_num<<endl;
	
	}
	


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
