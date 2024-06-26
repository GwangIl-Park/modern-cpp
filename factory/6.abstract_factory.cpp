#include <iostream>
#include <memory>
#include <map>

using namespace std;

class HotDrink
{
public:
  virtual void prepare(int volume) = 0;
};

class Tea : HotDrink
{
public:
  void prepare(int volume) override
  {
    cout << "Tea를 준비해요 " << volume << endl;
  }
};

class Coffee : HotDrink
{
public:
  void prepare(int volume) override
  {
    cout << "Coffee를 준비해요 " << volume << endl;
  }
};

// unique_ptr<HotDrink> make_drink(string type)
// {
//   unique_ptr<HotDrink> drink;
//   if(type == "Tea")
//   {
//     drink = make_unique<Tea>();
//     drink->prepare();
//   }
//   else
//   {
//     drink = make_unique<Coffee>();
//     drink->prepare();
//   }
// }

class HotDrinkFactory
{
public:
  virtual unique_ptr<HotDrink> make() const = 0;
};

class TeaFactory : HotDrinkFactory
{
public:
  unique_ptr<HotDrink> make() const override
  {
    return make_unique<Tea>();
  }
};

class CoffeeFactory : HotDrinkFactory
{
public:
  unique_ptr<HotDrink> make() const override
  {
    return make_unique<Coffee>();
  }
};

class DrinkFactory
{
  map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
  DrinkFactory()
  {
    hot_factories["coffee"] = make_unique<CoffeeFactory>();
    hot_factories["tea"] = make_unique<TeaFactory>();
  }

  unique_ptr<HotDrink> make_drink(const string& name)
  {
    auto drink = hot_factories[name]->make();
    drink->prepare(200);
    return drink;
  }
};