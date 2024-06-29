#include <iostream>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace std;

class Address
{
public:
  Address(const string& street, const string& city, int suite)
   : street(street), city(city), suite(suite){}
  string street, city;
  int suite;
private:
  friend class boost::serialization::access;
  template<class Ar> void serialization(Ar& ar, const unsigned int version)
  {
    ar& street;
    ar& city;
    ar& suite;
  }
};

class Contact
{
public:
  string name;
  Address *address;

  Contact();
  Contact(string name, Address *address)
   : name(name), address(address){}

private:
  friend class boost::serialization::access;
  template<class Ar> void serialization(Ar& ar, const unsigned int version)
  {
    ar& name;
    ar& address;
  }
};

int main()
{
  auto clone = [](const Contact& c)
  {
    ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << c;
    string s = oss.str();

    istringstream iss(oss.str());
    boost::archive::text_iarchive ia(iss);
    Contact result;
    ia >> result;

    return result;
  };

  Contact john{"",new Address{"123 East Dr", "London", 0}};
  Contact jane = clone(john);
  jane.name = "Jane";
  return 0;
}