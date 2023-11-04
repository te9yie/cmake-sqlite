cmake_minimum_required(VERSION 3.16)
project(sqlite3_examples)

add_executable(use_sqlite3 use_sqlite3.cpp)
target_compile_features(use_sqlite3 PRIVATE cxx_std_20)
target_link_libraries(use_sqlite3 PRIVATE sqlite3)
