# WASM OpenGL project



## Build
To build the project you need to have CMake and optionally Emscripten if you
wish to build WASM. 

Create a directory called build in the root project folder and run the command bellow.

To build normal executable for linux:
```
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
```

To build and run WASM: 
```
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake ..
emmake make
ermun --no_browser --port 8000 hello.html
```