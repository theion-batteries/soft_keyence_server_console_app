cd C:/
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

.\vcpkg install yaml-cpp:x64-windows
.\vcpkg install sockpp:x64-windows

.\vcpkg integrate install

