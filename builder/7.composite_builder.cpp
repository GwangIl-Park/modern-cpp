#include <iostream>
#include <string>

using namespace std;

class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;

class Person
{
  string street_address, post_code, city;
  string company_name, position;
  int annual_income = 0;

  Person(){}

public:
  static PersonBuilder create();

  friend std::ostream& operator<<(std::ostream& os, const Person& obj)
  {
    return os
      << "street_address: " << obj.street_address
      << " post_code: " << obj.post_code
      << " city: " << obj.city
      << " company_name: " << obj.company_name
      << " position: " << obj.position
      << " annual_income: " << obj.annual_income;
  }

  friend class PersonBuilder;
  friend class PersonAddressBuilder;
  friend class PersonJobBuilder;
};

class PersonBuilderBase
{
protected:
  Person& person;
  explicit PersonBuilderBase(Person& person)
    : person{person}
  {}
public:
  operator Person() const
  {
    return std::move(person);
  }

  PersonAddressBuilder lives() const;
  PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase
{
  Person p;
public:
  PersonBuilder() : PersonBuilderBase{p}
  {
  }
};

class PersonAddressBuilder : public PersonBuilderBase
{
  typedef PersonAddressBuilder self;
public:
  explicit PersonAddressBuilder(Person& person)
    : PersonBuilderBase{person}{}
  
  self& at(string street_address)
  {
    person.street_address = street_address;
    return *this;
  }

  self& with_postcode(string post_code)
  {
    person.post_code = post_code;
    return *this;
  }

  self& in(string city)
  {
    person.city = city;
    return *this;
  }
};

class PersonJobBuilder : public PersonBuilderBase
{
  typedef PersonJobBuilder self;
public:
  explicit PersonJobBuilder(Person& person)
    : PersonBuilderBase{person}{}
  
  self& at(string company_name)
  {
    person.company_name = company_name;
    return *this;
  }

  self& as_a(string position)
  {
    person.position = position;
    return *this;
  }

  self& earning(int annual_income)
  {
    person.annual_income = annual_income;
    return *this;
  }
};

PersonAddressBuilder PersonBuilderBase::lives() const
{
  return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilderBase::works() const
{
  return PersonJobBuilder{person};
}

PersonBuilder Person::create()
{
  return PersonBuilder{};
}

int main()
{
  Person p = Person::create()
    .lives().at("123 London Road")
            .with_postcode("SW1")
            .in("London")
    .works().at("Programsoft")
            .as_a("consultant")
            .earning(10e6);

  cout << p << endl;
  return 0;
}
