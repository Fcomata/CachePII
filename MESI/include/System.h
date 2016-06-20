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
#ifndef SYSTEM_H
#define SYSTEM_H
#include "Cache.h"
#include <iostream>
//! Clase System
/*! Esta clase representa un sistema de dos CPU con un Cache compartido
 * L2 y un Cache individual L1 con protocolo MESI
 */
 enum cpu{
	CPU0,CPU1
 };
 enum cache{
	L11,L12,L22
 };
 //!Clase System
/*!
 * Esta clase implementa una simulación de un sistema con dos CPU, cada 
 * una con un caché L1 y un caché L2 compartido.
 * Para el caché L1 se implementó el protocolo MESI para asegurar
 * coherencia.
 */
class System{
    public:
		//! Método Constructor sin parámetros
		/*! Este constructor forma dos Cache(), cuyos tamaños aun no han
		 * sido definidos
		 */
        System();
        //! Método Contructor a partir de dos caches
        /*! Este metodo construye un objeto System, el cual tendra un 
         * Cache L1 del tamaño del caché del primer parámetro, y un 
         * cache L2 del tamaño del segundo
         */
		System(Cache,Cache);
		//! Método Destructor.
		//! Actualmente no implementado.       
		virtual ~System();
		//! Método Settag.
		/*! Escribe un tag que represente la dirección(u32) deseada, se
		 * especifica el CPU (cpu) que realiza la acción, que puede ser
		 * de lectura(R) o de escritura(W) (bool)
		 */ 
        void settag(cpu,bool,u32);
        //! Método gettotalmisses.
        //! Retorna la cantidad de misses que ocurrieron en los 3 cachés.
        int gettotalmisses(void);
        //! Método gettotalhits
        //! Retorna la cantidad de hits que ocurrieron en los 3 cachés.
        int gettotalhits(void);
        //! Metodo getvalidbit
        /*! Retorna el valor de válido(validbit) [MOD,EXC,SHA,INV]
         *	para la dirección de memoria deseada(u32) en el Caché(cache)
         * especificado.
         */
        validbit getvalid(cache,u32);
    protected:
    private:
		//! Variable Privada L1
		//! Almacena 2 caches del mismo tamaño para las 2 CPUs
		vector<Cache> L1;
		//! Variable Privada L2
		//! Almacena el caché compártido L2.
		Cache L2;
};

#endif // SYSTEM_H
