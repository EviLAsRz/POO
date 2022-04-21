
EXES = test-fechacadena-consola test-P1-auto cadena_check fecha_check
CXX = clang++
CXXFLAGS = -g -Wall -std=c++11 -pedantic
CPPFLAGS = -DP1 -I../Tests-auto -I. 
VPATH = ../Tests-auto:.

CLASSES = fecha.o cadena.o

.PHONY: all clean

all: $(EXES)

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o $(CLASSES)
	$(CXX) $(CXXFLAGS) $^ -o $@

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

test-fechacadena-consola: test-fechacadena-consola.o $(CLASSES)
	$(CXX) $(CXXFLAGS) $^ -o $@

cadena_check fecha_check: cadena_check.cpp fecha_check.cpp
	make -f Make_check.mk

check: cadena_check fecha_check
	./cadena_check cadena.cpp
	./fecha_check fecha.cpp 
clean:

	$(RM) $(EXES) *.o
