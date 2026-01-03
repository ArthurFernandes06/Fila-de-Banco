ALL:	main

main:	main.o logtree.o fila_fifo.o escalonador.o
		gcc main.o logtree.o fila_fifo.o escalonador.o -o main -lm

main.o:	main.c escalonador.h fila_fifo.h logtree.h
		gcc -c main.c

logtree.o:	logtree.c logtree.h
		gcc -c logtree.c

fila_fifo.o: fila_fifo.c fila_fifo.h
		gcc -c fila_fifo.c

escalonador.o: escalonador.c fila_fifo.h escalonador.h 
		gcc -c escalonador.c

clean:
		rm -f main *.o