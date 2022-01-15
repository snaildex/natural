if not exist "build" mkdir build
cd "build"
cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_TOOLCHAIN_FILE="D:/Projects/vcpkg/scripts/buildsystems/vcpkg.cmake" %~dp0
cd %~dp0