PROTOC=../../bin/protoc

all:service client
	
service:service.cpp
	gcc $^ -o $@ -I../../include -L../../lib -lsofa-pbroc
client:client.cpp
	gcc $^ -o $@ -I../../include -L../../lib -lsofa-pbrpc
clean:
	rm -f main  
