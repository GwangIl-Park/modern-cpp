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

  string str(int indent = 0) const
  {
    string result = "<"+name+">"+text;
    for(auto element : elements) {
      result+="<"+element.name+">"+element.text+"</"+element.name+">";
    }
    return result+"</"+name+">";
  }

protected:
  HtmlElement() {}
  HtmlElement(const string& name, const string& text)
    : name(name), text(text) {}
};

class HtmlBuilder
{
public:
  operator HtmlElement() const {return root;}
  HtmlElement root;

  HtmlBuilder(string root_name) {root.name = root_name;}

  HtmlBuilder* add_child(string child_name, string child_text)
  {
    HtmlElement e{child_name, child_text};
    root.elements.emplace_back(e);
    return this;
  }

  HtmlElement build() const;

  string str() {return root.str();}
};

HtmlElement HtmlBuilder::build() const
{
  return root;
}

int main()
{
  HtmlElement e = *HtmlElement::build("ul")
                  ->add_child("li", "hello")
                  ->add_child("li", "world");
  cout << e.str() << endl;
  return 0;
}