# cmake-sqlite

## Usage

```cmake
include(FetchContent)

FetchContent_Declare(
    sqlite
    GIT_REPOSITORY https://github.com/te9yie/cmake-sqlite
    GIT_TAG main
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(sqlite)

...
target_link_libraries(xxxx PRIVATE sqlite)
```
