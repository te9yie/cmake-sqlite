# cmake-sqlite3

## Usage

```cmake
include(FetchContent)

FetchContent_Declare(
    sqlite3
    GIT_REPOSITORY https://github.com/te9yie/cmake-sqlite3
    GIT_TAG main
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(sqlite3)

...
target_link_library(xxxx PRIVATE sqlite3)
```
