monke src/core/* src/external/* src/types/*:
	g++ -fPIC -shared src/core/* src/external/* src/types/* -Iinclude -o build/libmonke.so
	sudo cp build/libmonke.so /usr/local/lib/