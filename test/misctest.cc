#include "util.hh"
#include "iostream"

using namespace mlcppl;

int main()
{
  char * a = "char * a";
  const char * b = "const char * b";
    
  cout << a << '\n';
  cout << b << '\n';
  cout << cpl(a) << '\n';
  cout << cpl(b) << '\n';
    
  return 0;
}
