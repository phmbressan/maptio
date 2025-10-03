all:
	cmake -B build -S . && cmake --build build

test:
	ctest --test-dir build

docs:
	doxygen Doxyfile

clean:
	rm -rf build

bind:
	pip install -e .