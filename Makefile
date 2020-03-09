TARGET=uno

all:
	$(CXX) -std=c++11 shell.cpp */*.cpp -o $(TARGET)
	#make clean

*.o: *.cpp *.hpp */*.cpp */*.hpp
	$(CXX) -std=c++11 *.cpp */*.cpp -c

clean:
	rm *.o

test:
	make all && ./uno
