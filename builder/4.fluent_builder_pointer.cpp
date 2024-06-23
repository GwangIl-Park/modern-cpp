#include <iostream>
#include <vector>

using namespace std;

class HtmlElement
{
public:
  string name;
  string text;
  
  vector<HtmlElement> elements;

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

  string str() {return root.str();}
};

int main()
{
  HtmlBuilder *builder = new HtmlBuilder("ul");
  builder->add_child("li", "hello")->add_child("li", "world");
  cout << builder->str() << endl;
  return 0;
}