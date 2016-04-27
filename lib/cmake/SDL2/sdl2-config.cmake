# sdl2 cmake project-config input for ./configure scripts

set(prefix "/v/filer4b/v38q001/rlorey/Downloads/SDL2-2.0.4/build/lib") 
set(exec_prefix "${prefix}")
set(libdir "${exec_prefix}/lib")
set(SDL2_PREFIX "/v/filer4b/v38q001/rlorey/Downloads/SDL2-2.0.4/build/lib")
set(SDL2_EXEC_PREFIX "/v/filer4b/v38q001/rlorey/Downloads/SDL2-2.0.4/build/lib")
set(SDL2_LIBDIR "${exec_prefix}/lib")
set(SDL2_INCLUDE_DIRS "${prefix}/include/SDL2")
set(SDL2_LIBRARIES "-L${SDL2_LIBDIR} -Wl,-rpath,${libdir} -lSDL2 ")
