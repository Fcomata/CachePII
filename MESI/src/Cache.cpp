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
Cache::~Cache(){
	
}
void Cache::setpair(Cache *pair){
	this->pair = pair;
}
bool Cache::settag(u32 memaddress, bool action){ //hay que cambiar la operación porque utilizaba validbit, Si existe un error de fijo esta aquí.
	bool miss = 1; //Hay que a;adir el caso trivial sin paralelismo, croe que esta en la otra compu.
	bool incache = 0;
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
			if(tag == this->gettag(set,i) && this->getvalid(set,i)){
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
		for(int i = 0; i<this->blockamm;i++){
			if(tag == this->gettag(set,i) && this->getvalid(set,i)==INV){
				for(int j =0; j<pair->blockamm;j++){
					if(tag == pair->gettag(set, j) && pair->getvalid(set,j) !=INV){
						pair->setvalid(set,j,SHA);
						this->setvalid(set,i,SHA);
						incache = 1;
					}
					else{
						this->setvalid(set,i,EXC);
						incache = 0;					
					}
				}
			}
		}
	}
	else if(action==W){ 
		for(int i =0; i<this->blockamm;i++){
			if(tag == this->gettag(set,i) &&(this->getvalid(set,i) != INV)){
				incache =1;
				this->setvalid(set,i,MOD);
				if(this->getvalid(set,i) == SHA){
					for(int j =0; j<pair->blockamm;j++){
						if(tag == pair->gettag(set,j)){
							pair->setvalid(set,j,INV);			
						}
					}				
				}
			}
			else if(tag == this->gettag(set,i) && this->getvalid(set,i) == INV){
				this->setvalid(set,i,MOD);
				incache =0;
				for(int j =0; j<pair->blockamm;j++){
					if(tag == pair->gettag(set,j)){
						pair->setvalid(set,i,INV);
						incache =1;
					}
				}			
			}
		}

	}	
	if(!incache){
		assoc = this->getassoc(set);
		this->cache[set][assoc].settag(tag);
		this->setvalid(set,assoc,EXC); //cambie a EXC, era 1
		if(action==W){
		this->setvalid(set,assoc,MOD);		
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





