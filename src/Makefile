#
# Lots of variableising to do here...
#

campc: main.o ui.o time.o
	cc -lncurses main.o ui.o time.o -o campc

main.o: main.c
	cc -c main.c -o main.o

ui.o: ui.c
	cc -c ui.c -o ui.o

time.o: time.c
	cc -c time.c -o time.o

clean:
	rm -vf *.o campc
