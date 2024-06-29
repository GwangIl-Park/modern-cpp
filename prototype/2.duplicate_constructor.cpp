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
  Contact(string name, Address *address)
   : name(name), address(address){}
  // Contact(const Contact& other)
  //  : name(other.name)
  // {
  //   address->street = other.address->street;
  //   address->city = other.address->city;
  //   address->suite = other.address->suite;
  // }
  Contact(const Contact& other)
   : name(other.name), address(new Address(*other.address)){}
  
  Contact& operator=(const Contact& other)
  {
    if(this==&other)
      return *this;
    name = other.name;
    address = other.address;
    return *this;
  }

  string name;
  Address *address;
};

int main()
{
  // Contact worker{"",Address{"123 East Dr", "London", 0}};
  // Contact john = worker;
  // john.name = "John";
  // john.address.suite = 2;

  Contact worker{"",new Address{"123 East Dr", "London", 0}};
  Contact john = worker;
  john.name = "John";
  john.address->suite = 2;
  return 0;
}