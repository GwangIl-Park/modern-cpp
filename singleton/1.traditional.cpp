#include <iostream>

using namespace std;

class Database
{
protected:
  Database() {/*aaaa*/}
public:
  static Database& get()
  {
    static Database database;
    return database;
  }
  Database(Database const&) = delete;
  Database(Database&&) = delete;
  Database& operator=(Database const&) = delete;
  Database& operator=(Database&&) = delete;

  static Database& get() {
    static Database* database = new Database();
    return *database;
  }
};