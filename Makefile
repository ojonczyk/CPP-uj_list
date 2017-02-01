main: main.cpp uj_list.hpp list_tester.hpp
	/usr/bin/g++ -std=c++11 -Wall -pedantic -lcppunit  main.cpp -o main
run: main
	./main
