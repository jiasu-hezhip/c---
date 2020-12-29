cmake_minimum_required(VERSION 3.17)
project(c__test1)

set(CMAKE_CXX_STANDARD 14)

add_executable(c__test1 main.cpp header/speechManager.h source/speechManager.cpp header/speaker.h)

include_directories("./header")
include_directories("./source")