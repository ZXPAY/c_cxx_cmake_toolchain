@echo Configure the makefile
cmake -S . -B ./build -G"Ninja" -DCMAKE_TOOLCHAIN_FILE=utils/gcc-toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_DANNYDSP=ON
@echo ===================== completed =====================
