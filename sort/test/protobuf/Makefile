PROTOC=../../bin/protoc

hello.pb.cc:hello.proto
	$(PROTOC) hello.proto --cpp_out=.

clean:
	rm -f main
