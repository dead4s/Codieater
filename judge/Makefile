CC = g++
CFLAGS =  -c -Iiclude

judge : main.o ProblemInfo.o ExecuteBox.o config.o childproc.o JudgeResult.o languageType.o TestCaseResult.o
	$(CC) -o judge main.o ProblemInfo.o ExecuteBox.o config.o childproc.o JudgeResult.o languageType.o TestCaseResult.o -lseccomp

main.o : main.cpp system/parse.hpp core/grade.hpp
	$(CC) $(CFLAGS) -o $@ main.cpp

childproc.o : core/childproc.cpp core/childproc.hpp
	$(CC) $(CFLAGS) -o $@ $< 

ExecuteBox.o : core/ExecuteBox.hpp core/ExecuteBox.cpp lang/* core/Seccomp.hpp
	$(CC) $(CFLAGS) -o $@ core/ExecuteBox.cpp

TestCaseResult.o : IO/TestCaseResult.cpp IO/TestCaseResult.hpp
	$(CC) $(CFLAGS) -o $@ $<

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
