all: boost-1 boost-1-clang
	

boost-1:
	g++ -g -I/usr/local/include -L/usr/local/lib -lboost_thread -o boost-1 main.cpp

boost-1-clang:
	clang++ -g -I/usr/local/include -L/usr/local/lib -lboost_thread -o boost-1-clang main.cpp
	
clean:
	rm -f boost-1 boost-1-clang

