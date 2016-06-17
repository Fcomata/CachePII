#include "System.h"

System::System(){
	this->L2 = Cache();
	vector<Cache> presystem(2,Cache());
	this->L1 = presystem;	
	this->L1[0].setpair(L1[1]);
	this->L1[1].setpair(L1[0]);
}
System::System(Cache L1,Cache L2){
	vector<Cache> presystem(2,L1);
	this->L1 = presystem;
	this->L2 = L2;
	this->L1[0].setpair(L1[1]);
	this->L1[1].setpair(L1[0]);
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
	totalhits += this->L1[1].getmisses();
	totalhits += this->L2.getmisses();
	return totalhits;
}

System::~System()
{
    //dtor
}
