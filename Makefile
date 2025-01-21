all: src/main.cpp src/options.cpp submodules
	cc -Wall -O src/main.cpp src/options.cpp -o bin/rvz-convert -lstdc++

submodules:
