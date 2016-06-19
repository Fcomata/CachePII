all: 

S:Secuencial.cpp
	mpic++ Secuencial.cpp -o Secuencial && ./Secuencial
P:Paralelo.cpp
	mpic++ Paralelo.cpp -o Paralelo && mpirun -np 4 Paralelo
clean:
	rm Paralelo && rm Secuencial

