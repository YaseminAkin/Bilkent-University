#/**
#* Title: Hash Tables
#* Author: Yasemin Akın
#* ID: 22101782
#* Section: 001
#* Homework: 4
#* Description: Makefile file */

hw4: main.o HashTable.o
	g++ main.o HashTable.o -o hw4

main.o: main.cpp HashTable.h KmerNode.h
	g++ -c main.cpp

HashTable.o: HashTable.cpp HashTable.h KmerNode.h
	g++ -c HashTable.cpp

clean:
	rm -f *.o hw4
