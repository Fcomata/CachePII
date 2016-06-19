/*  
    This file is part of EstructurasII.

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
#include<math.h>
#ifndef BLOQUE_H
#define BLOQUE_H
#include <iostream>
typedef unsigned long u32;
enum validbit{
	MOD,EXC,SHA,INV
};
using namespace std;
//! Clase Bloque
/*! Esta clase implementa la estructura general de un bloque de memoria en el cache.
*	Para este caso, se considera que todas las direcciones de memoria son de 32 bits,
*	por lo tanto se utilizan unsigned long, o u32 para su abreviación.
*	Este bloque posee una implementación utilizando el Valid Bit.
*/
class Bloque{
    public:
	//! Método constructor sin parámetros.
	/*! Inicializa un  bloque que contiene 0 direcciones de memoria,
	*	la hace no valida y le asigna un tag de 0.
	*/
	Bloque();
	//! Método contructor con parámetro int tamano.
	/*! Inicializa un bloque que contine tamano direcciones de memoria.
	*	hace el bloque no valido y le asigna un tag de 0.
	*
	*/
	Bloque(int);
	//! Método constructor de copia.
	/*! Crea una copia de un bloque anteriormente establecido
	*
	*/
	Bloque(const Bloque&);
	//! Sobrecarga del operador "=".
	//! Se sobrecarga el operador para llamar al constructor de copia utilizando "=".
	Bloque &operator=(const Bloque&);
	//! Método Destructor.
	//! Actualmente no implementado.
	virtual ~Bloque();
	//! Método settag.
	/*! 
	*	Recibe un parámetro u32 para asignarle un tag a la dirección de memoria actual.
	*/
	void settag(u32);
	//! Método gettag.
	/*!
	*	Retorna el valor del tag que está asignado a este bloque.
	*/
	u32 gettag(void);
	//! Método getvalid.
	//! Retorna el valor del "Valid Bit" del bloque.
	validbit getvalid(void);
	//! Método setvalid.
	//! Recibe un parámetro bool para asignarle el estado al valid bit.
	void setvalid(validbit);
    protected:

    private:
	//! Variable privada int blocksize.
	//! Almacena la cantidad de direcciones de memoria que se utilizan en el cache.
    	int blocksize;
	//! Variable privada bool valid.
	//! Almacena el valor lógico del "Valid Bit"(2 bits).
    	validbit valid;
	//! Variable privada u32 tag.
	//! Almacena el tag. Se utiliza un u32 para evitar problemas de conversión a otro tipo de dato.
    	u32 tag;

};

#endif // BLOQUE_H
