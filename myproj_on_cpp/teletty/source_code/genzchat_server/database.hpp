#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

namespace DB{
    void createDB(const string& PATH) {
        sqlite3* DB;
        int exit = 0;

        exit = sqlite3_open(PATH.c_str(), &DB);
        if (exit != SQLITE_OK) {
          cerr << "something wrong with db";
        }

        string creatingsql = "CREATE TABLE IF NOT EXISTS USERS("
            "NAME TEXT NOT NULL,"
            "IP TEXT NOT NULL,"
            "PRIMARY KEY (NAME, IP));";
        char* messageError = nullptr;
        exit = sqlite3_exec(DB, creatingsql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
          cerr << "SQL error: " << messageError << endl;
          sqlite3_free(messageError);
        }
        sqlite3_close(DB);
    }

  bool insert(const string& PATH, const string& IP, const string& NAME) {
      sqlite3* DB; 
      int exit = sqlite3_open(PATH.c_str(), &DB);
      
      if (exit != SQLITE_OK) {
          cerr << "Cannot open database: " << sqlite3_errmsg(DB) << endl;
          return false;
      }
      
      string sqlcommand = "INSERT INTO USERS (NAME, IP) VALUES ('" + NAME + "', '" + IP + "');";
      
      char* messageError = nullptr;
      exit = sqlite3_exec(DB, sqlcommand.c_str(), NULL, 0, &messageError);
      
      if (exit != SQLITE_OK) {
          sqlite3_free(messageError);
      	  return false;
      }
      
      sqlite3_close(DB);

      return true;
  }
}

#endif
