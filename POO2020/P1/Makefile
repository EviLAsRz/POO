DIR = ../Tests-auto/
CXX = g++
STD = c++11
CXXFLAGS = -std=${STD} -g -pedantic -Wall
CPPFLAGS = -DP1 -I../Tests-auto -I.
LDFLAGS = -I$(DIR)
VPATH = ../Tests-auto:.
OBJS = test-P1-consola.o test-caso0-fecha-auto.o \
	test-caso0-cadena-auto.o test-auto.o fecha.o cadena.o cadena_check.o fecha_check.o
EXE = test-P1-auto test-P1-consola cadena_check fecha_check

all: test-P1-consola test-P1-auto

test: test-consola test-auto

test-consola: test-P1-consola
	./$<

test-auto: test-P1-auto
	./$<

test-P1-consola: test-P1-consola.o fecha.o cadena.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test-P1-consola.o: test-P1-consola.cpp fecha.hpp cadena.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o cadena.o fecha.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS)  $^ -o $@

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

fecha.o: fecha.cpp fecha.hpp 
	$(CXX) -c $(CXXFLAGS) $< -o $@

cadena.o: cadena.cpp cadena.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

cadena_check fecha_check: cadena_check.cpp fecha_check.cpp
	make -f Make_check.mk

check: cadena_check fecha_check
	./cadena_check cadena.cpp -- -std=${STD}
	./fecha_check fecha.cpp -- -std=${STD}

clean:
	$(RM)	$(OBJS) $(EXE)
