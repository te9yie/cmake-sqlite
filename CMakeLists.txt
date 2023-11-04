cmake_minimum_required(VERSION 3.16)
project(sqlite3)

option(SQLITE3_WITH_EXAMPLES "Builds examples for cmake_sqlite3" OFF)

include(FetchContent)

# sqlite3
FetchContent_Declare(
    sqlite
    URL https://www.sqlite.org/2023/sqlite-amalgamation-3440000.zip
    URL_HASH SHA3_256=91b5884ad3dd634f84a0096751d6c36812542e1e0042ad7b2ba059e639921d7e
    DOWNLOAD_EXTRACT_TIMESTAMP false)
FetchContent_MakeAvailable(sqlite)

add_library(sqlite3 STATIC ${sqlite_SOURCE_DIR}/sqlite3.c)
target_compile_definitions(sqlite3 PUBLIC
    SQLITE_ENABLE_FTS3
    SQLITE_ENABLE_FTS5
    SQLITE_ENABLE_RTREE
    SQLITE_ENABLE_DBSTAT_VTAB
    SQLITE_ENABLE_RBU
    SQLITE_ENABLE_SESSION)
target_include_directories(sqlite3 PUBLIC ${sqlite_SOURCE_DIR})

if(SQLITE3_WITH_EXAMPLES)
    add_subdirectory(examples)
endif()