#include "Cache.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
	string aux, str;
	u32 auxi;
	int argvi[3];
	Cache my_cache;
	if(argc !=4){
		cout<<"Invalid Argument."<< endl;
		return 0;
	}
	for(int i =0; i<3; i++){
		argvi[i] = atoi(argv[i+1]);
	}
	my_cache = Cache(argvi[1],argvi[0],argvi[2]);
	ifstream file("aligned.trace");
	while(getline(file,str)){
		aux = "0x" + str.substr(0,8); // toma los 8 primeros caracteres.
		auxi = stoul(aux,nullptr,16);
		my_cache.settag(auxi,0);
	}
	cout<<"Misses: "<< my_cache.getmisses() << endl;
	cout<<"Hits: " << my_cache.gethits() <<endl;

}
