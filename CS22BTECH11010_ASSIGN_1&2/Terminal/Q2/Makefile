Myshell.exe : main.o myls.o mycp.o mymv.o myps.o mypse.o mygrep.o
	gcc main.o myls.o mycp.o mymv.o myps.o mypse.o mygrep.o -o Myshell -lreadline
main.o : main.c header.h
	gcc -c main.c -o main.o -lreadline
myls.o : myls.c header.h
	gcc -c myls.c -o myls.o -lreadline
mycp.o : mycp.c header.h	
	gcc -c mycp.c -o mycp.o -lreadline
mymv.o : mymv.c header.h
	gcc -c mymv.c -o mymv.o -lreadline
myps.o : myps.c header.h
	gcc -c myps.c -o myps.o -lreadline
mypse.o : mypse.c header.h
	gcc -c mypse.c -o mypse.o -lreadline
mygrep.o : mygrep.c header.h
	gcc -c mygrep.c -o mygrep.o -lreadline