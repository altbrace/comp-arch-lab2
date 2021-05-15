all: sc.o rk.o mbc.o myTerm.o sat.o main.o
	gcc -o sc sc.o rk.o mbc.o myTerm.o main.o
	gcc -o sat sat.o sc.o

sc: sc.o rk.o mbc.o myTerm.o main.o
	gcc -o sc sc.o rk.o mbc.o myTerm.o main.o

sat: sat.o sc.o
	gcc -o sat sat.o sc.o

main.o: main.c
	gcc -c main.c

sat.o: sat.c
	gcc -c sat.c

sc.o: SimpleComputer/sc.c
	gcc -c SimpleComputer/sc.c

rk.o: myReadkey/rk.c
	gcc -c myReadkey/rk.c

mbc.o: myBigChars/mbc.c
	gcc -c myBigChars/mbc.c

myTerm.o: myTerm/myTerm.c
	gcc -c myTerm/myTerm.c

clean:
	rm sc.o rk.o mbc.o myTerm.o sat.o


