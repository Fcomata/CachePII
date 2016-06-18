all: 

C: Criba.cpp
	g++ Criba.cpp -o Criba
S: Secuencial.cpp
	mpic++ -fopenmp Secuencial.cpp -o Secuencial
P:Paralelo.cpp
	mpic++ Paralelo.cpp -o Paralelo
	mpirun -np 4 Paralelo
clean:
	rm Secuencial
	rm Paralelo
	rm Criba

