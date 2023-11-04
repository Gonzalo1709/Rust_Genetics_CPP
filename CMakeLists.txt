cmake_minimum_required(VERSION 3.25)
project(RustGenetics2)

set(CMAKE_CXX_STANDARD 17)

add_executable(RustGenetics2 main.cpp definitions.h CloneManager.h CloneManager.cpp CloneProcessor.h CloneProcessor.cpp ProcessManager.cpp ProcessManager.h)
