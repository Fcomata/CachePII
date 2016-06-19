#include "System.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	int d;
	Cache L1;
	Cache L2;
	L1 = Cache(2,2,2);
	L2 = Cache(4,4,4);
	System cpus(L1,L2);
	cout<<"Se creo el sistema, la dirección debería ser invalida"<<endl;
	cout<<cpus.gettotalhits()<<endl;
	
	
	d =cpus.getvalid(L11,0x00AF00);
	cout<<d<<endl; //Antes de que se escriba Debería ser invalid
	
	cpus.settag(CPU0,R,0x00AF00); //escribe en caché Ier miss
	
	d =cpus.getvalid(L11,0x00AF00); 
	cout<<d<<endl; //Se escribio deberia esta r en exc
	
	
	cpus.settag(CPU1,R,0x00AF00); //Escribe en el caché
	
	d= cpus.getvalid(L11,0x00AF00);
	cout<<d<<endl; // Debería dar shared
	
	
	d= cpus.getvalid(L12,0x00AF00);
	cout<<d<<endl; // Debería dar shared
	

	cout<<cpus.gettotalmisses()<<endl;
	cout<<cpus.gettotalhits()<<endl;
}
