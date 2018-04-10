ex1.o: ex1.c
	gcc -Wall ex1.c -o ex1.o

clean:
	rm -rf *.o;
