#include <iostream>
#include <memory>
using namespace std;

class Address
{
public:
  Address(const string& street, const string& city, int suite)
   : street(street), city(city), suite(suite){}
  string street, city;
  int suite;
};

class Contact
{
public:
  Contact(string name, Address address)
   : name(name), address(new Address(address)){}
  string name;
  Address *address;
};

class EmployeeFactory
{
public:
  static Contact main;
  static Contact aux;

  static unique_ptr<Contact> NewMainOfficeEmployee(string name, int suite)
  {
    return NewEmployee(name, suite, main);
  }
  static unique_ptr<Contact> NewAuxOfficeEmployee(string name, int suite)
  {
    return NewEmployee(name, suite, main);
  }
private:
  static unique_ptr<Contact> NewEmployee(string name, int suite, Contact& proto)
  {
    auto result = make_unique<Contact>(proto);
    result->name = name;
    result->address->suite = suite;
    return result;
  }
};

int main()
{
  auto john = EmployeeFactory::NewMainOfficeEmployee("John Doe", 123);
  auto jane = EmployeeFactory::NewAuxOfficeEmployee("Jane Doe", 124);
  return 0;
}