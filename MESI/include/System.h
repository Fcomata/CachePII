#ifndef SYSTEM_H
#define SYSTEM_H
#include "Cache.h"
//! Clase System
/*! Esta clase representa un sistema de dos CPU con un Cache compartido
 * L2 y un Cache individual L1 con protocolo MESI
 */
 enum cpu{
	CPU0,CPU1
 };
class System
{
    public:
        System();
		System(Cache,Cache,Cache);
        virtual ~System();
        void settag(cpu,bool,u32);
        int gettotalmisses(void);
        int gettotalhits(void);
    protected:
    private:
		vector<Cache> L1;
		Cache L2;
};

#endif // SYSTEM_H
