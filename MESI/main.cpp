#include "System.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	int d;
	string aux, str;
	u32 auxi;
	int i =1;
	Cache L1;
	Cache L2;
	L1 = Cache(512,16,1);
	L2 = Cache(4096,16,1);
	System cpus(L1,L2);
	ifstream file("aligned.trace");
	while(getline(file,str)){
		aux = "0x" + str.substr(0,8); // toma los 8 primeros caracteres.
		auxi = stoul(aux,nullptr,16);
		aux = str.substr(12,13);
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
	}
	cout<<"Se creo el sistema, la dirección debería ser invalida"<<endl;
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
}
