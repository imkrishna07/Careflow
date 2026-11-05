#pragma once
#include "Patient.h"
#include <sqlite3.h>
#include <string>
#include <vector>
class Database {
  sqlite3* handle=nullptr;
  void execute(const char* sql);
public:
  explicit Database(const std::string& path);
  ~Database();
  Database(const Database&)=delete;
  Database& operator=(const Database&)=delete;
  void load(std::vector<Patient>& waiting,std::vector<Patient>& treated);
  void save(const std::vector<Patient>& waiting,const std::vector<Patient>& treated);
};
