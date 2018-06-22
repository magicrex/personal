.PHONY:all
#all:testDB_main
#	g++ $^ -o $@ -std=c++11 -lpthread -lboost_system -lboost_filesystem -I/usr/include/mysql -I/usr/local/include/mysql++ -L/usr/lib64/mysql -lmysqlpp -lmysqlclient -lnsl -lm

all:httpserver login_cgi

httpserver:httpserver.cpp  httpserver_main.cpp
	g++ $^ -o $@ -std=c++11 -lpthread -lboost_system -lboost_filesystem -I/usr/include/mysql -I/usr/local/include/mysql++ -L/usr/lib64/mysql -lmysqlpp -lmysqlclient -lnsl -lm -g

#gi_main:cgi_main.cpp
#   g++ $^ -o $@ -std=c++11 -lpthread -lboost_system -lboost_filesystem -I/usr/include/mysql -I/usr/local/include/mysql++ -L/usr/lib64/mysql -lmysqlpp -lmysqlclient -lnsl -lm
#   cp cgi_main ./wwwroot/add

login_cgi:login_cgi.cpp
	g++ $^ -o $@ -std=c++11 -lboost_system -lboost_filesystem -I/usr/include/mysql -I/usr/local/include/mysql++ -L/usr/lib64/mysql -lmysqlpp -lmysqlclient -lnsl -lm -lctemplate -lpthread -g
	cp login_cgi ./wwwroot/login_cgi
.PHONY:clean
clean:
#	rm testDB_main
#	rm -f httpserver cgi_main
	rm -f httpserver login_cgi ./wwwroot/login_cgi
