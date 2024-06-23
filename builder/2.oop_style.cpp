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

int main()
{
  string words[] = {"hello", "world"};
  HtmlElement list{"ul", ""};
  for(auto w : words)
    list.elements.emplace_back(HtmlElement{"li", w});
  printf(list.str().c_str());
  return 0;
}