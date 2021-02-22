project(Hippo)

set(CMAKE_CXX_STANDARD 20)


add_library(fixo SHARED fixo.cpp)
add_executable(hippo main.cpp)
target_link_libraries(hippo fixo)
