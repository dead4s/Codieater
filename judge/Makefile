CC = g++
CFLAGS =  -c -Iiclude

main : main.o ProblemInfo.o ExecuteBox.o config.o cpp14.o childproc.o JudgeResult.o
	$(CC) -o $@ main.o ProblemInfo.o ExecuteBox.o config.o cpp14.o childproc.o JudgeResult.o

main.o : main.cpp util/parse.hpp
	$(CC) $(CFLAGS) -o $@ main.cpp 

ProblemInfo.o : util/ProblemInfo.cpp util/ProblemInfo.hpp
	$(CC) $(CFLAGS) -o $@ util/ProblemInfo.cpp 

ExecuteBox.o : lang/ExecuteBox.cpp lang/ExecuteBox.hpp 
	$(CC) $(CFLAGS) -o $@ lang/ExecuteBox.cpp

config.o : config.cpp config.hpp
	$(CC) $(CFLAGS) -o $@ config.cpp

cpp14.o : lang/CPP_14.hpp lang/CPP_14.cpp
	$(CC) $(CFLAGS) -o $@ lang/CPP_14.cpp

childproc.o : process/childproc.hpp process/childproc.cpp
	$(CC) $(CFLAGS) -o $@ process/childproc.cpp

JudgeResult.o : JudgeResult.hpp JudgeResult.cpp
	$(CC) $(CFLAGS) -o $@ JudgeResult.cpp

clean :
	rm *.o main 