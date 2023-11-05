#include <sqlite3.h>
#include <cstdlib>
#include <iostream>

int callback(void* param, int col_cnt, char** col_val, char** col_name) {
  for (int i = 0; i < col_cnt; i++) {
    std::cout << col_name[i] << ": " << col_val[i] << std::endl;
  }
  return SQLITE_OK;
}

int exec_sql(sqlite3* db,
             const char* sql,
             sqlite3_callback callback = nullptr) {
  char* errmsg = nullptr;
  auto r = sqlite3_exec(db, sql, callback, nullptr, &errmsg);
  if (r != SQLITE_OK) {
    std::cerr << errmsg << std::endl;
  }
  return r;
}

int main() {
  if (auto r = sqlite3_initialize(); r != SQLITE_OK) {
    std::cerr << sqlite3_errstr(r) << std::endl;
    return EXIT_FAILURE;
  }

  sqlite3* db = nullptr;
  if (auto r = sqlite3_open_v2(
          "test.db", &db, SQLITE_OPEN_MEMORY | SQLITE_OPEN_READWRITE, nullptr);
      r != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db) << std::endl;
    goto shutdown;
  }

  if (exec_sql(db, "create table users (id INTEGER, name TEXT);") !=
      SQLITE_OK) {
    goto shutdown;
  }

  if (exec_sql(db, "insert into users values (1, 'Alice');") != SQLITE_OK) {
    goto shutdown;
  }

  if (exec_sql(db, "insert into users values (2, 'Bob');") != SQLITE_OK) {
    goto shutdown;
  }

  if (exec_sql(db, "select * from users;", callback) != SQLITE_OK) {
    goto shutdown;
  }

shutdown:
  sqlite3_close(db);
  sqlite3_shutdown();

  return EXIT_SUCCESS;
}
