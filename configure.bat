echo Configure the makefile
cmake -S . -B ./build -G"Ninja" -DCMAKE_TOOLCHAIN_FILE=utils/arm-gcc-toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
echo ===================== completed =====================
