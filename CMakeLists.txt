cmake_minimum_required(VERSION 3.18)
project(rozhkovdmitrii_lib)

set(CMAKE_CXX_STANDARD 14)

add_library(rozhkovdmitrii_lib
  Log.cpp
  Log.h

  ExceptionStream.h
)

target_include_directories(rozhkovdmitrii_lib PUBLIC .)