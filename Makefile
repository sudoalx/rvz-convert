all: src/main.cpp src/options.cpp submodules preinstall
	cc -Wall -O src/main.cpp src/options.cpp -o bin/rvz-convert -lstdc++

submodules:
	git submodule update --init --recursive --depth=1
	cmake -S lib/dolphin -B lib/dolphin/cmake-build
	make -C lib/dolphin/cmake-build dolphin-tool
	make -C lib/wiimms-iso-tools/project

submodules-windows:
	git submodule update --init --recursive --depth=1
	mingw64-cmake -S lib/dolphin -B lib/dolphin/cmake-build-windows
	mingw64-make -C lib/dolphin/cmake-build-windows dolphin-tool
	mingw64-make -C lib/wiimms-iso-tools/project

preinstall:
	cp lib/wiimms-iso-tools/project/bin/wit bin/
	cp lib/dolphin/cmake-build/Binaries/dolphin-tool bin/

windows: submodules-windows

clean:
	rm -rf lib/dolphin/cmake-build/*
	rm -rf lib/dolphin/cmake-build-windows/*
	rm bin/*
