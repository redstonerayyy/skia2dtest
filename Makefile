.PHONY: build
build:
	clear
	cmake -B ./build .
	make -C ./build
	cp ./build/skiatest .
	chmod +x skiatest
	./skiatest

clean:
	rm -rf ./build