CC = g++
CFLAGS =  -c -Iiclude

judge : main.o ProblemInfo.o ExecuteBox.o config.o childproc.o JudgeResult.o languageType.o 
	$(CC) -o judge main.o ProblemInfo.o ExecuteBox.o config.o childproc.o JudgeResult.o languageType.o 

main.o : main.cpp system/parse.hpp core/grade.hpp
	$(CC) $(CFLAGS) -o $@ main.cpp

childproc.o : core/childproc.cpp core/childproc.hpp
	$(CC) $(CFLAGS) -o $@ $< 

ExecuteBox.o : core/ExecuteBox.hpp core/ExecuteBox.cpp lang/*
	$(CC) $(CFLAGS) -o $@ core/ExecuteBox.cpp

JudgeResult.o : IO/JudgeResult.cpp IO/JudgeResult.hpp
	$(CC) $(CFLAGS) -o $@ $<

ProblemInfo.o : IO/ProblemInfo.cpp IO/ProblemInfo.hpp
	$(CC) $(CFLAGS) -o $@ $<

config.o : system/config.cpp system/config.hpp
	$(CC) $(CFLAGS) -o $@ $<

languageType.o : IO/languageType.cpp IO/languageType.hpp
	$(CC) $(CFLAGS) -o $@ $<

clean : 
	rm *.o 
