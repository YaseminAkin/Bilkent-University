hw2: BSTNode.o BST.o KmerTree.o main.o
	g++ BSTNode.o BST.o KmerTree.o main.o -o hw2
	
main.o: main.cpp
	g++ -c main.cpp
	
BSTNode.o: BSTNode.cpp BSTNode.h
	g++ -c BSTNode.cpp
	
BST.o: BST.cpp BST.h
	g++ -c BST.cpp
	
analysis.o: KmerTree.cpp KmerTree.h
	g++ -c KmerTree.cpp
	
clean:
	rm *.o hw2
