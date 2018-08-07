.PHONY:all

BASE=-std=c++11 -lboost_system -lboost_filesystem
DATA1=-I/usr/include/mysql -I/usr/local/include/mysql++ 
DATA2=-L/usr/lib64/mysql -lmysqlpp -lmysqlclient -lnsl -lm
TEMP=-lctemplate -lpthread
all:httpserver login_cgi regist_cgi update_cgi upfile_cgi delfile_cgi modimess_cgi addstu_cgi addpro_cgi set_cgi delnote_cgi delproj_cgi select_cgi

httpserver:httpserver.cpp  httpserver_main.cpp
	g++ $^ -o $@ $(BASE) -lpthread $(DATA1) $(DATA2) -g

login_cgi:login_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -g
	cp login_cgi ./wwwroot/login_cgi

select_cgi:select_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -g
	cp select_cgi ./wwwroot/select_cgi
regist_cgi:regist_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -g
	cp regist_cgi ./wwwroot/regist_cgi

update_cgi:update_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -g
	cp update_cgi ./wwwroot/update_cgi
upfile_cgi:upfile_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -lboost_regex -g
	cp upfile_cgi ./wwwroot/upfile_cgi
delfile_cgi:delfile_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -lboost_regex -g
	cp delfile_cgi ./wwwroot/delfile_cgi
delnote_cgi:delnote_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -lboost_regex -g
	cp delnote_cgi ./wwwroot/delnote_cgi
delproj_cgi:delproj_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -lboost_regex -g
	cp delproj_cgi ./wwwroot/delproj_cgi
modimess_cgi:modimess_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -lboost_regex -g
	cp modimess_cgi ./wwwroot/modimess_cgi
addstu_cgi:addstu_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -lboost_regex -g
	cp addstu_cgi ./wwwroot/addstu_cgi
addpro_cgi:addpro_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -lboost_regex -g
	cp addpro_cgi ./wwwroot/addpro_cgi
set_cgi:set_cgi.cpp
	g++ $^ -o $@ $(BASE) $(DATA1) $(DATA2) $(TEMP) -lboost_regex -g
	cp set_cgi ./wwwroot/set_cgi
.PHONY:clean
clean:
	rm -f httpserver login_cgi regist_cgi update_cgi upfile_cgi delfile_cgi modimess_cgi addstu_cgi addpro_cgi
	rm -f ./wwwroot/login_cgi ./wwwroot/regist_cgi ./wwwroot/update_cgi ./wwwroot/upfile_cgi delfile_cgi modimess_cgi
	rm -f ./wwwroot/delfile_cgi ./wwwroot/modimess_cgi ./wwwroot/addstu_cgi ./wwwroot/addpro_cgi
	rm -f set_cgi ./wwwroot/set_cgi delnote_cgi ./wwwroot/delnote_cgi delproj_cgi ./wwwroot/delproj_cgi
	rm -f select_cgi ./wwwroot/select_cgi
