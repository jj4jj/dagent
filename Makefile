build_:
	./automake.sh build

clean:
	./automake.sh clean
	rm -rf build/

install:
	./automake.sh install

test:
	./automake.sh test