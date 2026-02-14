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
        
        string triggersql = "CREATE TRIGGER limit_names_per_ip "
            "BEFORE INSERT ON USERS "
            "BEGIN "
            "    SELECT CASE "
            "        WHEN (SELECT COUNT(*) FROM USERS WHERE IP = NEW.IP) >= 3 "
            "        THEN RAISE(ABORT, 'Maximum 3 names per IP address') "
            "    END; "
            "END;";
        
        exit = sqlite3_exec(DB, triggersql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
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

    static int check_ip_callback(void* data, int argc, char** argv, char** azColName) {
        bool* exists = static_cast<bool*>(data);
        *exists = true;
        return 0;
    }

    bool addUser(const string name) {
        sqlite3* DB;
        string sqlcommand = "SELECT IP FROM USERS WHERE NAME = '" + name + "'";
        char* messageError = nullptr;
        
        int exit = sqlite3_open("users.db", &DB);
        
        bool nameExists = false;
        
        exit = sqlite3_exec(DB, sqlcommand.c_str(), check_ip_callback, &nameExists, &messageError);
        
        if (exit != SQLITE_OK) {
            cerr << "Error in selectData function." << endl;
            sqlite3_free(messageError);
            sqlite3_close(DB);
            return false;
        }
        
        sqlite3_close(DB);
        
        return nameExists;
    }
}

#endif
