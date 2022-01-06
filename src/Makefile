all: cryptic.exe

cryptic.exe: main.o interface.o encryption.o file_handler.o include/interface.h
	gcc main.o interface.o encryption.o file_handler.o -o ../cryptic.exe

interface.o: include/encryption.h include/file_handler.h
	gcc -c interface.c

encryption.o: include/file_handler.h
	gcc -c encryption.c

file_handler.o: 
	gcc -c file_handler.c