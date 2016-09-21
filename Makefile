########################################
##
## Makefile
## LINUX compilation
##
##############################################





#FLAGS
C++FLAG = -g -std=c++14 -Wall -pedantic

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I.

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib


#First Program (ListTest)

Cpp_OBJ=image.o p1.o

PROGRAM1=p1
PROGRAM2=p2
PROGRAM3=p3
PROGRAM4=p4

$(PROGRAM1): $(Cpp_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ) $(INCLUDES) $(LIBS_ALL)


all:
	make $(PROGRAM1)


clean:
	(rm -f *.o;)
	(rm -f p1;)
