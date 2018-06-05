.PHONY:all
all:httpserver cgi_main

httpserver:httpserver.cpp  httpserver_main.cpp
	g++ $^ -o $@ -std=c++11 -lpthread -lboost_system -lboost_filesystem 

cgi_main:cgi_main.cpp
	g++ $^ -o $@ -std=c++11 -lpthread -lboost_system -lboost_filesystem 

.PHONY:clean
clean:
	rm -f httpserver cgi_main
