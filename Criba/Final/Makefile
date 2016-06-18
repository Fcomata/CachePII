all: 


P:Criba.cpp
	mpic++ -fopenmp Criba.cpp -o Paralelo
	mpirun -np 4 Paralelo
S:Criba.cpp
	mpic++ -fopenmp CribaSecuencial.cpp -o Secuencial
	./Secuencial
clean:
	rm Paralelo
	

