all:
	cmake -B build -S . && cmake --build build

test:
	ctest --test-dir build

clean:
	rm -rf build
