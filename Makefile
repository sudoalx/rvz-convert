all: src/main.cpp src/options.cpp submodules preinstall
	cc -Wall -O src/main.cpp src/options.cpp -o bin/rvz-convert -lstdc++

submodules:
	git submodule update --init --recursive --depth=1
	cmake -S lib/dolphin -B lib/dolphin/cmake-build
	make -C lib/dolphin/cmake-build dolphin-tool
	make -C lib/wiimms-iso-tools/project

preinstall:
	cp lib/wiimms-iso-tools/project/bin/wit bin/
	cp lib/dolphin/cmake-build/Binaries/dolphin-tool bin/

clean:
	rm -rf lib/dolphin/cmake-build/*
	rm -rf lib/dolphin/cmake-build-windows/*
	rm bin/*
