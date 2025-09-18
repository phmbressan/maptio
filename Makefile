all:
	cmake -B build -S . && cmake --build build

test:
	ctest --test-dir build

docs:
	doxygen Doxyfile

clean:
	rm -rf build

bind:
	python3 setup.py build_ext --inplace

bind-install: bind
	pip install .