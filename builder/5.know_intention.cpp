#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct HtmlBuilder;

class HtmlElement
{
  friend HtmlBuilder;
public:
  string name;
  string text;
  vector<HtmlElement> elements;
  const size_t intent_size = 2;

  static unique_ptr<HtmlBuilder> build(const string& root_name)
  {
    return make_unique<HtmlBuilder>(root_name);
  }

protected:
  HtmlElement() {}
  HtmlElement(const string& name, const string& text)
    : name(name), text(text) {}

  string str(int indent = 0) const
  {
    string result = "<"+name+">"+text;
    for(auto element : elements) {
      result+="<"+element.name+">"+element.text+"</"+element.name+">";
    }
    return result+"</"+name+">";
  }
};

class HtmlBuilder
{
public:
  HtmlElement root;

  HtmlBuilder(string root_name) {root.name = root_name;}

  HtmlBuilder* add_child(string child_name, string child_text)
  {
    HtmlElement e{child_name, child_text};
    root.elements.emplace_back(e);
    return this;
  }

  HtmlElement build() const {
    return root;
  }

  string str() {return root.str();}
};

int main()
{
  auto builder = HtmlElement::build("ul");
  builder->add_child("li", "hello")->add_child("li", "world");
  cout << builder->str() << endl;
  return 0;
}