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
#include <vector>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef CACHE_H
#define CACHE_H
#define R 0
#define W 1
//! Clase Cache.
/*!
*	Esta clase implementa una estructura básica de cache para palabras
*	de 32 bits. Se implementa el cache como una matriz de bloques de
*	memoria (Vease Bloque.h).
*/
class Cache{
	public:
		//! Método Constructor sin parámetros.
		/*! Construye un cache de tamaño 1, sin sets y con un solo bloque
		*	de memoria, el cual tendra unicamente una dirección de memoria.	
		*	Esta dirección de memoria apuntará a 0.	
		*/
		Cache();
		//! Método Constructor preferido.
		/*! Contruye un cache con set cantidad de sets, blocks cantidad de
		*	bloques y blocksizes cantidad de direcciones por bloque. Que son
		*	los parámetros en ese orden.
		*/
		Cache(int, int, int);
		//! Método Constructor con pareja(Para Cache compartido).
		/*! Permite establecer una pareja al cache, de modo que el mismo
		* la puede usar para fisgonear, y modificar el dato de los demas caches,
		* Entre demás funciones.
		*/
		Cache(int,int,int,Cache*);
		//! Constructor de copia
		//! Se utiliza para crea un caché a partir de otro.
		Cache(const Cache&);
		//! Sobrecarga del operador "=".
		//! Se sobrecarga el operador para llamar al constructor de copia utilizando "=".
		Cache &operator=(const Cache&);
		//! Método Destructor.
		//! Actualmente no implementado.
		virtual ~Cache();
		//! Método settag.
		/*!	Le pasa un u32 memaddress al cache, para que el mismo vea si hay
		*	hit o miss, y procede a extraer el tag para escribirlo en el 
			bloque correspondiente. el bool pasa el valor de Read o Write
		*/
		bool settag(u32,bool);
		//! Metodo gettag.
		//! Retorna el tag que está en la dirección (set, assoc) de la matriz del caché.
		u32 gettag(int, int);
		//! Metodo getmisses.
		//! Retorna la cantidad de misses que se han producido desde que se creo el caché.
		int getmisses();
		//! Método gethits.
		//! Retorna la cantidad de hits que se han producido desde que se creo el caché.
		int gethits();
		//! Establece una pareja a este caché.
		void setpair(Cache*);
		//! Método getvalid con parámetro U32
		//!getvalid en funcion de la dirección de memoria
		validbit getvalid(u32);

	protected:
		
	private:
		//! Método privado getassoc(int index).
		/*!	Este método forma parte de la política de reemplazo del cache.
		*	El método seleccióna el bloque a reemplazar a partir de la entrada
		*	index, que es el set en el cual se va a guardar la dirección.
		*	La politica que se implementó fue aleatoria.
		*/	
		int getassoc(int);
		//! Método privado setvalid.
		/*! Este método cambia el bit de valido de un bloque en específico que 
		*	es accesado a partir de las coordenadas (set, assoc).
		*/
		void setvalid(int, int, validbit);
		//! Método privado getvalid.
		/*! Este método retorna el valor del bit de valido del bloque que se 
		*	accesa a partir de las coordenadas (set, assoc).
		*/
		validbit getvalid(int, int);
		//! Variable privada int blockquant.
		//! Almacena la cantidad de bits que ocupa el offset de la dirección de cache.
		int blockquant;
		//! Variable privada indexquant.
		//! Almacena la cantidad de bits que ocupa el index de la dirección de cache.
		int indexquant;
		//! Variable privada tagquant.
		//! Almacena la cantidad de bits que ocupa el tag de la dirección de cache.
		int tagquant;
		//! Variable privada blockamm.
		//! Almacena la cantidad de bloques por set que se guardan en el cache(asociatividad).
		int blockamm;
		//! Variable privada sets.
		//! Almacena la cantidad de sets en el caché.
		int sets;
		//! Variable privada blocksize.
		//! Almacena la cantidad de palabras bloque de cache.
		int blocksize;
		//! Variable privada cache.
		//! Estructura matricial de bloques elegida para la implementación de cache.
		vector< vector<Bloque> > cache;
		//! Variable privada misses.
		//! Almacena la cantidad de misses que se obtuvieron desde que se creo el cache.
		int misses;
		//! Variable privada hits.
		//! Almacena la cantidad de hits que se obtuvieron desde que se creo el cache.
		int hits;
		//! Variable privada *pair.
		//! Almacena la posición de memoria de la pareja del cache. (En caso de cache compartido con protocolo MESI).
		Cache *pair;

};

#endif //CACHE_H


