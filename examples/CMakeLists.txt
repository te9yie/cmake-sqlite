cmake_minimum_required(VERSION 3.16)
project(sqlite_examples)

add_executable(use_sqlite use_sqlite.cpp)
target_compile_features(use_sqlite PRIVATE cxx_std_20)
target_link_libraries(use_sqlite PRIVATE sqlite)
