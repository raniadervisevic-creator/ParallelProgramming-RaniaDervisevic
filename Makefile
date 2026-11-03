CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17 -march=native

TARGET = globalsum_bench

all: $(TARGET)

$(TARGET): globalsum.cpp
	$(CXX) $(CXXFLAGS) globalsum.cpp -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) results.txt
