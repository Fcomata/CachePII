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
#include "Bloque.h"
Bloque::Bloque(){
	this->blocksize = 0;
	this->valid = INV;
	this->tag =0;

}
Bloque::Bloque(const Bloque& other){
	this->blocksize = other.blocksize;
	this->valid = other.valid;
	this->tag = other.tag;
}
Bloque::Bloque(int tamano){
	this->blocksize = tamano;
	this->valid = INV;
	this->tag =0;

}

Bloque &Bloque::operator=(const Bloque& other){
	if(this!= &other){
		this->blocksize = other.blocksize;
		this->valid = other.valid;
		this->tag = other.tag;

	}
	return *this;
}

void Bloque::settag(u32 tag){
	this->tag = tag;
}

u32 Bloque::gettag(void){
	return this->tag;
}
validbit Bloque::getvalid(void){
	return this->valid;
}
void Bloque::setvalid(validbit valid){
	this->valid = valid;
}

Bloque::~Bloque()
{
    //dtor
}
