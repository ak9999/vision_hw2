# Makefile edited by Abdullah Khan

#FLAGS
C++FLAGS = -g -std=c++14 -Wall -pedantic

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAGS) $(INCLUDES) -c $< -o $@

.cpp.o:
	g++ $(C++FLAGS) $(INCLUDES) -c $< -o $@


#Including
INCLUDES=  -I.

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib

p1_obj=image.o p1.o
p2_obj=image.o p2.o
p3_obj=image.o p3.o
p4_obj=image.o p4.o

PROGRAM1=p1
PROGRAM2=p2
PROGRAM3=p3
PROGRAM4=p4

all: $(PROGRAM1) $(PROGRAM2) $(PROGRAM3) $(PROGRAM4)

$(PROGRAM1): $(p1_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(p1_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM2): $(p2_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(p2_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM3): $(p3_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(p3_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM4): $(p4_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(p4_obj) $(INCLUDES) $(LIBS_ALL)

package:
	(zip KHAN_HW2.zip *.h *.cc *.cpp Makefile README.txt)

clean:
	(rm -f *.o;)
	(rm -f p1;)
	(rm -f p2;)
	(rm -f p3;)
	(rm -f p4;)
