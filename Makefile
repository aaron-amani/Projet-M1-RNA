all: RNA RNA_thread

perceptron.o: perceptron.c perceptron.h
	gcc	-c perceptron.c

RNA.o: RNA.c perceptron.h
	gcc -c RNA.c

RNA_thread.o: RNA_thread.c perceptron.h
	gcc -c RNA_thread.c


RNA: perceptron.o RNA.o
	gcc -o RNA perceptron.o RNA.o
	

RNA_thread: perceptron.o RNA_thread.o
	gcc -o RNA_thread perceptron.o RNA_thread.o
	

rm: 
	rm *.o 
	rm RNA_thread
	rm RNA


