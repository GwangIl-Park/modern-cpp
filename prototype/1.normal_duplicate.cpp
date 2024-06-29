#include <iostream>
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
   : name(name), address(address){}
  string name;
  Address address;
};

int main()
{
  Contact worker{"",Address{"123 East Dr", "London", 0}};
  Contact john = worker;
  john.name = "John";
  john.address.suite = 2;
  return 0;
}