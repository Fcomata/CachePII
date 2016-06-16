#ifndef CPU_H
#define CPU_H


class CPU
{
    public:
        CPU();
        virtual ~CPU();
        CPU(const CPU& other);

    protected:

    private:
};

#endif // CPU_H
/*

Politica :

Read Misses solo en invalid. (Se fetchea a los Shared o Exclusive States)
Write Solo hit en MOD O EXC, si SHA, todos los demas se invalidan.
EXC o SHA pueden cambiar a invalid en cualquier momento. Modified se debe hacer Write Back
Si esta en MOD, debe oler todos los intentos de read. 
Si está en en Sharedmse debe escuchar a invalidate o RFO
*/

