cmake_minimum_required(VERSION 3.16)
project(sqlite)

option(SQLITE_WITH_EXAMPLES "Builds examples for cmake-sqlite" OFF)
# https://www.sqlite.org/amalgamation.html
option(SQLITE_ENABLE_FTS3 "enable SQLITE_ENABLE_FTS3" OFF)
option(SQLITE_ENABLE_FTS5 "enable SQLITE_ENABLE_FTS5" OFF)
option(SQLITE_ENABLE_RTREE "enable SQLITE_ENABLE_FTS5" OFF)
option(SQLITE_ENABLE_DBSTAT_VTAB "enable SQLITE_ENABLE_DBSTAT_VTAB" OFF)
option(SQLITE_ENABLE_RBU "enable SQLITE_ENABLE_RBU" OFF)
option(SQLITE_ENABLE_SESSION "enable SQLITE_ENABLE_SESSION" OFF)
# https://www.sqlite.org/compile.html
option(SQLITE_RECOMMENDED_OPTIONS "recommended options for sqlite" ON)

include(FetchContent)

# sqlite_amalgamation
FetchContent_Declare(
    sqlite_amalgamation
    URL https://www.sqlite.org/2023/sqlite-amalgamation-3440000.zip
    URL_HASH SHA3_256=91b5884ad3dd634f84a0096751d6c36812542e1e0042ad7b2ba059e639921d7e
    DOWNLOAD_EXTRACT_TIMESTAMP false)
FetchContent_MakeAvailable(sqlite_amalgamation)

# sqlite
add_library(sqlite STATIC ${sqlite_amalgamation_SOURCE_DIR}/sqlite3.c)
target_compile_definitions(sqlite PUBLIC
    $<$<BOOL:${SQLITE_ENABLE_FTS3}>:SQLITE_ENABLE_FTS3>
    $<$<BOOL:${SQLITE_ENABLE_FTS5}>:SQLITE_ENABLE_FTS5>
    $<$<BOOL:${SQLITE_ENABLE_RTREE}>:SQLITE_ENABLE_RTREE>
    $<$<BOOL:${SQLITE_ENABLE_DBSTAT_VTAB}>:SQLITE_ENABLE_DBSTAT_VTAB>
    $<$<BOOL:${SQLITE_ENABLE_RBU}>:SQLITE_ENABLE_RBU>
    $<$<BOOL:${SQLITE_ENABLE_SESSION}>:SQLITE_ENABLE_SESSION>
    $<$<BOOL:${SQLITE_RECOMMENDED_OPTIONS}>:
        SQLITE_DQS=0
        SQLITE_THREADSAFE=0
        SQLITE_DEFAULT_MEMSTATUS=0
        SQLITE_DEFAULT_WAL_SYNCHRONOUS=1
        SQLITE_LIKE_DOESNT_MATCH_BLOBS
        SQLITE_MAX_EXPR_DEPTH=0
        SQLITE_OMIT_DECLTYPE
        SQLITE_OMIT_DEPRECATED
        SQLITE_OMIT_PROGRESS_CALLBACK
        SQLITE_OMIT_SHARED_CACHE
        SQLITE_USE_ALLOCA
        SQLITE_OMIT_AUTOINIT>)
target_include_directories(sqlite PUBLIC ${sqlite_amalgamation_SOURCE_DIR})

if(SQLITE_WITH_EXAMPLES)
    add_subdirectory(examples)
endif()
