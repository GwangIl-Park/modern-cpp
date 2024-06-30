#include <map>
#include <iostream>
#include <vector>
class Database
{
public:
  virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase : public Database
{
  SingletonDatabase() {/*데이터베이스에서 데이터 읽기*/}
  std::map<std::string, int> capitals;
public:
  SingletonDatabase(SingletonDatabase const&) = delete;
  void operator=(SingletonDatabase const&) = delete;

  static SingletonDatabase& get()
  {
    static SingletonDatabase db;
    return db;
  }

  int get_population(const std::string& name) override
  {
    return capitals[name];
  }
};

class SingletonRecordFinder
{
  int total_population(std::vector<std::string> names)
  {
    int result = 0;
    for(auto& name : names)
      result += SingletonDatabase::get().get_population(name);
    return result;
  }
};

TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
  SingletonRecordFinder rf;
  std::vector<std::string> names{"Seoul", "Mexico City"};
  int tp = rf.total_population(names);
  EXPECT_EQ(17500000 + 17400000, tp);
}

class ConfigurableRecordFinder
{
  explicit ConfigurableRecordFinder(Database& db)
    : db{db}{}
  int total_population(std::vector<std::string> names)
  {
    int result = 0;
    for(auto& name : names)
      result += db.get_population(name);
    return result;
  }
  Database& db;
}

class DummyDatabase : public Database
{
  std::map<std::string, int> capitals;
public:
  DummyDatabase()
  {
    capitals["a"] = 1;
    capitals["b"] = 2;
    capitals["c"] = 3;
  }
  int get_population(const std::string& name) override
  {
    return capitals[names];
  }
};

TEST(RecordFinderTests, DummyTotalPopulationTest)
{
  DummyDatabase db{};
  ConfigurableRecordFinder rf{db};
  EXPECT_EQ(4, rf.total_population(
    std::vector<std::string>{"a", "b"};
  ));
}