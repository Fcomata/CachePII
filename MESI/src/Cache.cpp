/*  This file is part of EstructurasII.

    EstructurasII is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EstructurasII is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EstructurasII.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Cache.h"
#include <iostream>
#include <bitset>
using namespace std;
Cache::Cache(){
	this->blockamm =0;
	this->sets =0;
	this->blocksize =0;
	vector<Bloque> setdir (this->sets, Bloque(this->blocksize));
	vector< vector<Bloque> > precache (blockamm, setdir);
	this->cache = precache;
	this->blockquant =0;
	this->tagquant =0;
	this->indexquant =0;
	this->hits =0;
	this->misses =0;
	this->pair =this;
}
Cache::Cache(int set, int blocks, int blocksizes){
	this->blockamm = blocks;
	this->sets = set;
	this->blocksize = blocksizes;
	vector<Bloque> setdir (this->blockamm, Bloque(this->blocksize));
	vector< vector<Bloque> > precache (this->sets, setdir);
	this->cache = precache;
	this->blockquant = ceil(log2(this->blocksize));
	this->indexquant = ceil(log2(this->sets));
	this->tagquant = 32 -this->blockquant - this->indexquant;
	this->hits =0;
	this->misses =0;
	this->pair = this;
	
}
Cache::Cache(int set, int blocks,int blocksizes, Cache* pair){
	this->blockamm = blocks;
	this->sets = set;
	this->blocksize = blocksizes;
	vector<Bloque> setdir (this->blockamm, Bloque(this->blocksize));
	vector< vector<Bloque> > precache (this->sets, setdir);
	this->cache = precache;
	this->blockquant = ceil(log2(this->blocksize));
	this->indexquant = ceil(log2(this->sets));
	this->tagquant = 32 -this->blockquant - this->indexquant;
	this->hits =0;
	this->misses =0;
	this->pair = pair;
	
}
Cache::Cache(const Cache& other){
	this->blockamm = other.blockamm;
	this->sets = other.sets;
	this->blocksize = other.blocksize;
	this->cache = other.cache;
	this->blockquant = other.blockquant;
	this->indexquant = other.indexquant;
	this->hits = 0;
	this->misses =0;
	this->pair = this;
}
Cache &Cache::operator=(const Cache& other){
	if(this!= &other){
		this->blockamm = other.blockamm;
		this->sets = other.sets;
		this->blocksize = other.blocksize;
		this->cache = other.cache;
		this->blockquant = other.blockquant;
		this->indexquant = other.indexquant;
		this->hits = 0;
		this->misses =0;
		this->pair = this;
	}
	return *this;
}

Cache::~Cache(){
	
}
void Cache::setpair(Cache *pair){
	this->pair = pair;
}
bool Cache::settag(u32 memaddress, bool action){ //hay que cambiar la operación porque utilizaba validbit, Si existe un error de fijo esta aquí.
	validbit c1;
	validbit c2;
	bool miss = 1; //Hay que a;adir el caso trivial sin paralelismo, croe que esta en la otra compu.
	bool incache = 0;
	bool nenter =1;
	u32 tag,index,temp;
	int set,assoc;
	temp = blockquant+indexquant;
 	tag = memaddress >> temp;
	temp = tag << temp;
	temp = memaddress - temp;
	index = temp >> blockquant;
	set = (int) index;
	if(this->pair == this){
		for(int i = 0; i<this->blockamm;i++){
			if(tag == this->gettag(set,i) && this->getvalid(set,i) != INV){
				miss = 0;
				this->hits++;
				break;
			}
		}
		if(miss){
			assoc = this->getassoc(set);
			this->cache[set][assoc].settag(tag);
			this->setvalid(set,assoc,EXC);
			this->misses++;
		}
	}
	else{
	if(action== R){
		//cout<<"entre a R"<<endl;
		//c1 = getvalid(memaddress);
		//cout<<"getvalid"<< c1<<endl;
		if(this->getvalid(memaddress) != INV){ //Conserva el estado
			incache =1;
			this->hits++;
			c1 = this->getvalid(memaddress);
			//cout<<"Este es el getvalid: " << c1<<endl;
			c2 = pair->getvalid(memaddress);
		}
		else if(pair->getvalid(memaddress) !=INV){ //ambos son shared
			//cout<<"aquí deberia entrar"<<endl;
			incache =0;
			this->misses++;
			c1 = SHA;
			c2 = SHA;
			assoc = this->getassoc(set);
			this->cache[set][assoc].settag(tag);
			this->setvalid(set,assoc,SHA);
			for(int i = 0; i<this->blockamm;i++){
				if(tag == pair->gettag(set,i) && pair->getvalid(set,i) != INV){
					//if(this->getvalid(set,i) == MOD) incache =0;
					//cout<<"Entré aquí"<<endl;
					if(pair->getvalid(set,i) == MOD){
						incache =0;
					}
					pair->setvalid(set,i,SHA);
					break;
				}
					
			}
		}
		else{ //El propio es EXC
			incache =0;
			this->misses++;
			c1 = EXC;
			c2 = pair->getvalid(memaddress);
			assoc = this->getassoc(set);
			this->cache[set][assoc].settag(tag);
			this->setvalid(set,assoc,EXC);
		}
	}
	
	else if(action==W){  //Falta modificar para los writes
		//cout<<"La acción es W"<<endl;
		if(this->getvalid(memaddress) != INV && this->getvalid(memaddress) != SHA){
			//cout<<"opción 1"<<endl;
			c1 = MOD;
			incache =1;
			this->hits++;
			for(int i =0; i<this->blockamm; i++){
				if(tag == this->gettag(set,i)){
					this->setvalid(set,i,MOD);
				}
			}			
		}
		else if(this->getvalid(memaddress) != INV && this->getvalid(memaddress) == SHA){
			//cout<<"opción 2"<<endl;
			this->hits++;
			c1 = MOD;
			c2 = INV;
			incache = 1;
			for(int i =0; i<this->blockamm; i++){
				if(tag == this->gettag(set,i)){
					//cout<<"escribe MOD a self"<<endl;
					this->setvalid(set,i,MOD);
				}
			}
			for(int i =0; i<pair->blockamm;i++){
				if(tag == pair->gettag(set,i)){
					pair->setvalid(set,i,INV);
				}
			}
		}
		
		else if(this->getvalid(memaddress) == INV && pair->getvalid(memaddress) == INV){
			//cout<<"opción 3"<<endl;
			this->misses++;
			c1 = MOD;
			incache =0;
			assoc = this->getassoc(set);
			this->cache[set][assoc].settag(tag);
			this->setvalid(set,assoc,MOD);
		}
		else{ //aqui tengo un problema
			//cout<<"opción 4"<<endl;
			c1 = MOD;
			incache =0;
			assoc = this->getassoc(set);
			this->cache[set][assoc].settag(tag);
			this->setvalid(set,assoc,MOD);
			//cout<<"Ya modificó al 1"<<endl;
			//cout<<"tag: "<< tag<<endl;
			for(int i =0; i<pair->blockamm;i++){
				//cout<<"pair: "<<pair->gettag(set,i)<<endl;
				if(tag == pair->gettag(set,i)){
					//cout<<"aquí lo invalidé"<<endl;
					pair->setvalid(set,i,INV);
				}		
			}	
		}

	}	
	return incache;
}
}
u32 Cache::gettag(int set, int assoc){
	return this->cache[set][assoc].gettag();	
}

void Cache::setvalid(int set, int assoc, validbit valid){
	this->cache[set][assoc].setvalid(valid);
}
validbit Cache::getvalid(int set, int assoc){
	return this->cache[set][assoc].getvalid();
}
int Cache::getassoc(int index){ //Politica de reemplazo
	int randint;
	int notvalid[this->blockamm];
	int j =0;
	srand (time(NULL));
	for(int i =0; i < this->blockamm; i++){
				

		if(this->getvalid(index,i)==INV){ //Si es un bit invalido			
			notvalid[j] = i; //Guarda en un vector de no validos la posicion del bloque no valido
			j++;		
		}
				
	}
	if(j==0){// todos son validos
		randint = rand()%this->blockamm; //randomreplace en bloques!
		return randint;
	}
	else{
		randint = rand()%j;//randomreplace con j
		return notvalid[randint];
	}		
}
int Cache::getmisses(){
	return this->misses;	
}
int Cache::gethits(){
	return this->hits;
}
validbit Cache::getvalid(u32 memaddress){
	u32 tag,temp,index;
	int set;
	temp = blockquant + indexquant;
 	tag = memaddress >> temp;
	temp = tag << temp;
	temp = memaddress - temp;
	index = temp >> blockquant;
	set = (int) index;
	for(int i = 0; i<this->blockamm;i++){
		if(tag == this->gettag(set,i)){
			 return this->getvalid(set,i);
		 }
	 }
	 return INV;
	
}





