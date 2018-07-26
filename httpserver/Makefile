.PHONY:all

BASE=-std=c++11 -lboost_system -lboost_filesystem
DATA1=-I/usr/include/mysql -I/usr/local/include/mysql++ 
DATA2=-L/usr/lib64/mysql -lmysqlpp -lmysqlclient -lnsl -lm
TEMP=-lctemplate -lpthread
all:httpserver login_cgi regist_cgi update_cgi

httpserver:httpserver.cpp  httpserver_main.cpp
	g++ $^ -o $@ $(BASE) -lpthread $(DATA1) $(DATA2) -g
login_cgi:login_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -g
	cp login_cgi ./wwwroot/login_cgi

regist_cgi:regist_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -g
	cp regist_cgi ./wwwroot/regist_cgi

update_cgi:update_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -g
	cp update_cgi ./wwwroot/update_cgi
.PHONY:clean
clean:
	rm -f httpserver login_cgi login_cgi regist_cgi update_cgi
