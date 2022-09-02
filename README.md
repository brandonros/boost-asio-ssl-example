# boost-asio-ssl-example
Boost.Asio SSL example

## How to build

```shell
mkdir build && cd build
conan install --build=boost ..
cmake .. -G "Unix Makefiles" # Mac OS X / Linux
cmake .. -G "Visual Studio 16 2019" -A Win32 # Windows
cmake --build .
```
