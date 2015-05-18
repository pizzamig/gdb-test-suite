all: boost-2 boost-2-clang

boost-2:
	g++ -g -I/usr/local/include -L/usr/local/lib -lboost_thread -o boost-2 main.cpp

boost-2-clang:
	clang++ -g -I/usr/local/include -L/usr/local/lib -lboost_thread -o boost-2-clang main.cpp

clean:
	rm -f boost-2 boost-2-clang
