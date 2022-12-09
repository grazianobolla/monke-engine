monke:
	rm -rf build/
	mkdir build
	g++ -fPIC -shared src/core/* src/external/* src/types/* -Iinclude -o build/libmonke.so
	sudo cp build/libmonke.so /usr/local/lib/
	sudo cp -r include/monke/ /usr/local/include/