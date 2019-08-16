CC=g++ -std=c++11 -g
EXE_FILE=reservation

all: $(EXE_FILE)

$(EXE_FILE): main.cpp customer.o date.o customer.hpp date.hpp
	$(CC) main.cpp customer.o date.o -o $(EXE_FILE)

customer.o: customer.hpp customer.cpp
	$(CC) -c customer.cpp

date.o: date.hpp date.cpp
	$(CC) -c date.cpp

clean:
	rm -f *.o $(EXE_FILE)
