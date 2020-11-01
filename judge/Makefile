CC = g++
CFLAGS =  -c -Iiclude

main : main.o ProblemInfo.o ExecuteBox.o config.o cpp14.o
	$(CC) -o main main.o ProblemInfo.o ExecuteBox.o	config.o cpp14.o

main.o : main.cpp util/parse.hpp
	$(CC) $(CFLAGS) -o main.o main.cpp 

ProblemInfo.o : util/ProblemInfo.cpp util/ProblemInfo.hpp
	$(CC) $(CFLAGS) -o ProblemInfo.o util/ProblemInfo.cpp 

ExecuteBox.o : lang/ExecuteBox.cpp lang/ExecuteBox.hpp
	$(CC) $(CFLAGS) -o ExecuteBox.o lang/ExecuteBox.cpp

config.o : config.cpp config.hpp
	$(CC) $(CFLAGS) -o config.o config.cpp

cpp14.o : lang/CPP_14.hpp lang/CPP_14.cpp
	$(CC) $(CFLAGS) -o cpp14.o lang/CPP_14.cpp

clean :
	rm *.o main 