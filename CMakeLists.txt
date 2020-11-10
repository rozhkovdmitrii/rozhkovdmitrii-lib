cmake_minimum_required(VERSION 3.18)
project(rozhkovdmitrii-lib)

set(CMAKE_CXX_STANDARD 17)

add_library(rozhkovdmitrii-lib
  Log.cpp
  Log.h
  LogCfg.h
  LogCfg.cpp
  ExceptionStream.h
)

target_include_directories(rozhkovdmitrii-lib PUBLIC .)