mkdir -p build
cd build
cmake -S .. -B build -G "Ninja" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build . --config Release
cd ..
