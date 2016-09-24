#FLAGS
C++FLAG = -g -std=c++14 -Wall -pedantic

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES) -c $< -o $@

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES) -c $< -o $@


#Including
INCLUDES=  -I.

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib

p1_obj=image.o p1.o

p2_obj=image.o p2.o

PROGRAM1=p1
PROGRAM2=p2
PROGRAM3=p3
PROGRAM4=p4

all: $(PROGRAM1) $(PROGRAM2)

$(PROGRAM1): $(p1_obj)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(p1_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM2): $(p2_obj)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(p2_obj) $(INCLUDES) $(LIBS_ALL)

clean:
	(rm -f *.o;)
	(rm -f p1;)
	(rm -f p2;)
	(rm -f p3;)
	(rm -f p4;)
