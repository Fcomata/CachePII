all: 


Criba:Criba.cpp
	mpic++ Criba.cpp -o Paralelo
	mpirun -np 4 Paralelo
Secuencial:CribaSecuencial.cpp
	mpic++ CribaSecuencial.cpp -o Secuencial
	mpirun -np 1 Secuencial
Paralelo:Paralelo.cpp
	mpic++ Paralelo.cpp -o Paralelo
	mpirun -np 4 Paralelo
clean:
	rm Paralelo
	

