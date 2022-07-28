.PHONY: build
build:
	clear
	cmake -B ./build .
	make -C ./build
	cp ./build/skiatest ./src/skiatest
	chmod +x ./src/skiatest
	./src/skiatest

clean:
	rm -rf ./build