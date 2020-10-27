CC = g++
CFLAGS =  -c -Iiclude

main : main.o ProblemInfo.o 
	$(CC) -o main main.o ProblemInfo.o

main.o : main.cpp util/parse.hpp
	$(CC) $(CFLAGS) -o main.o main.cpp 

ProblemInfo.o : util/ProblemInfo.cpp util/ProblemInfo.hpp
	$(CC) $(CFLAGS) -o ProblemInfo.o util/ProblemInfo.cpp 

clean :
	rm *.o main 