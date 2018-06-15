.PHONY:all
all:httpserver cgi_main

httpserver:httpserver.cpp  httpserver_main.cpp
	g++ $^ -o $@ -std=c++11 -lpthread -lboost_system -lboost_filesystem -I/usr/include/mysql -I/usr/local/include/mysql++ -L/usr/lib64/mysql -lmysqlpp -lmysqlclient -lnsl -lm

cgi_main:cgi_main.cpp
	g++ $^ -o $@ -std=c++11 -lpthread -lboost_system -lboost_filesystem -I/usr/include/mysql -I/usr/local/include/mysql++ -L/usr/lib64/mysql -lmysqlpp -lmysqlclient -lnsl -lm
	cp cgi_main ./wwwroot/add

.PHONY:clean
clean:
	rm -f httpserver cgi_main
