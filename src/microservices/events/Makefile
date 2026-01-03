.PHONY: config build build-r run run-r


config:
	cmake \
		-S . \
		-B build \
		-G "Ninja Multi-Config" \
		-DCMAKE_TOOLCHAIN_FILE=/home/igor/Programs/vcpkg/scripts/buildsystems/vcpkg.cmake

build:
	cmake --build build

build-r:
	cmake --build build --config Release

run:
	./build/Debug/events

run-r:
	./build/Release/events
