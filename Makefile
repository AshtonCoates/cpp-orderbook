CXX = g++
CXXFLAGS = -std=c++20

orderbook: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp book.cpp -o orderbook

clean:
	rm -f orderbook
