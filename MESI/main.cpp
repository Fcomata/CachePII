#include "System.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){ // El archivo tiene 49642128 lineas
	bool flag = 0;
	char a;
	int d;
	string aux, str,c1,c2,l;
	u32 auxi;
	int i =0;
	int j =0;
	Cache L1;
	Cache L2;
	L1 = Cache(512,1,16);
	L2 = Cache(4096,1,16);
	System cpus(L1,L2);
	ifstream file("aligned.trace");
	while(getline(file,str)){
		i++;
		aux = "0x" + str.substr(0,8); // toma los 8 primeros caracteres.
		if(isspace(aux[9])){
			aux = "0x" +str.substr(0,7);
			flag =1;
		}
		auxi = stoul(aux,nullptr,16);
		aux = str.substr(12,13);
		if(flag){
			aux = str.substr(11,12);
		}
		flag =0;
		//cout<<aux<<endl;
		if(i%2 == 1 && aux == "L"){
			cpus.settag(CPU0,R,auxi);
		}
		else if(i%2 == 1 && aux =="S"){
			cpus.settag(CPU0,W,auxi);
		}
		else if(i%2 == 0 && aux == "L"){
			cpus.settag(CPU1,R,auxi);
		}
		else if(i%2 == 0 && aux =="S"){
			cpus.settag(CPU1,W,auxi);
		}
		
		if(i>= 49642119){
			if(i== 49642119){
			cout<<"CPU"<<"  "<<"Dirección"<<" Acción"<< " L11"<<" L12"<<" L2"<<endl;
			}
			d = cpus.getvalid(L11,auxi);
			switch(d){
				case INV:
					c1 = "INV";
					break;
				case MOD:
					c1 = "MOD";
					break;
				case EXC:
					c1 = "EXC";
					break;
				case SHA:
					c1 = "SHA";
					break;
				default:
					c1 = "ERROR";
					break;			
			}
			d = cpus.getvalid(L12,auxi);
			switch(d){
				case INV:
					c2 = "INV";
					break;
				case MOD:
					c2 = "MOD";
					break;
				case EXC:
					c2 = "EXC";
					break;
				case SHA:
					c2 = "SHA";
					break;
				default:
					c2 = "ERROR";
					break;			
			}
			d = cpus.getvalid(L22,auxi);
			switch(d){
				case INV:
					l = "INV";
					break;
				case MOD:
					l = "MOD";
					break;
				case EXC:
					l = "EXC";
					break;
				case SHA:
					l = "SHA";
					break;
				default:
					l = "ERROR";
					break;
				}
			cout<<"CPU"<<!(i%2)<<" "<<auxi<<"   "<<aux<<"   "<<c1<<" "<<c2<<" "<<l<< endl;
		}
	}
	cout<<"misses: "<<cpus.gettotalmisses()<<endl;
	cout<<"hits: "<<cpus.gettotalhits()<<endl;
}
	//cout<<"Se creo el sistema, la dirección debería ser invalida"<<endl;
	/*
	
	d =cpus.getvalid(L11,0x00AF00);
	cout<<d<<endl; //Antes de que se escriba Debería ser invalid
	
	cpus.settag(CPU0,R,0x00AF00); //escribe en caché Ier miss
	
	d =cpus.getvalid(L11,0x00AF00); 
	cout<<d<<endl; //Se escribio deberia esta W en EXC 
	
	
	cpus.settag(CPU1,R,0x00AF00); //Escribe en el caché segundo miss
	
	d= cpus.getvalid(L11,0x00AF00);
	cout<<"el que sigue es SHA"<<endl;
	cout<<d<<endl; // Debería dar INV
	
	
	d= cpus.getvalid(L12,0x00AF00);
	cout<<d<<endl; // Debería dar MOD
	
	cpus.settag(CPU1,W,0x00AF00);
	d = cpus.getvalid(L12,0x00AF00);
	cout<<d<<endl; //deberia ser mod
	d = cpus.getvalid(L11,0x00AF00);
	cout<<d<<endl; //deberia ser INV
	

	//cout<<cpus.gettotalmisses()<<endl;
	//cout<<cpus.gettotalhits()<<endl;
	*/ 
