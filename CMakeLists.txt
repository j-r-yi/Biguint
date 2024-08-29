cmake_minimum_required(VERSION 3.5)

project(HW9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HW9 main.cpp
    Biguint.h Biguint.cpp
    Bigint.h Bigint.cpp)

include(GNUInstallDirs)
install(TARGETS HW9
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
