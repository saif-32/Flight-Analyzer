
project2Exe: main.o route-records.o
	gcc main.o route-records.o -o project2Exe

main.o: main.c
	gcc -c main.c

route-records.o: route-records.c route-records.h
	gcc -c route-records.c

clean:
	rm *.o project2Exe