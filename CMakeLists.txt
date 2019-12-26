cmake_minimum_required(VERSION 3.10)
project(Pokemon)

add_compile_options(
  -std=c++1z
  -Wall
  -Werror
  -pedantic
  )

add_executable(Pokemon pokemon.cc)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
