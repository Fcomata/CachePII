#include "System.h"
using namespace std;
System::System(){
	this->L2 = Cache();
	this->L2.setpair(&this->L2);
	vector<Cache> presystem(2,Cache());
	this->L1 = presystem;	
	this->L1[0].setpair(&this->L1[1]);
	this->L1[1].setpair(&this->L1[0]);
}
System::System(Cache L1,Cache L2){ //Por aqui estoy perdiendo mis punteros
	vector<Cache> presystem(2,L1);
	this->L1 = presystem;
	this->L2 = L2;
	this->L2.setpair(&this->L2);
	this->L1[0].setpair(&this->L1[1]);
	this->L1[1].setpair(&this->L1[0]);
}
void System::settag(cpu pc,bool action,u32 tag){
	bool inL1;
	if(pc == CPU0){
		inL1 = this->L1[0].settag(tag,action);
		if(!inL1) this->L2.settag(tag,action);
		
	}
	else if(pc ==CPU1){
		inL1 = this->L1[1].settag(tag,action);
		if(!inL1) this->L2.settag(tag,action);
	}
}
int System::gettotalmisses(){
	int totalmisses;
	totalmisses = this->L1[0].getmisses();
	totalmisses += this->L1[1].getmisses();
	totalmisses += this->L2.getmisses();
	return totalmisses;
}
int System::gettotalhits(){
	int totalhits;
	totalhits = this->L1[0].gethits();
	totalhits += this->L1[1].gethits();
	totalhits += this->L2.gethits();
	return totalhits;
}

validbit System::getvalid(cache ca, u32 mem){
	validbit valid;
	switch(ca){
		case L11:
			valid = this->L1[0].getvalid(mem);
			break;
		case L12:
			valid = this->L1[1].getvalid(mem);
			break;
		case L22:
			valid = this->L2.getvalid(mem);
			break;
		default:
			valid = INV;
			break;
	}
	return valid;
	
}
System::~System()
{
    //dtor
}
