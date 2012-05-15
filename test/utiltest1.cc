#include "util.hh"

using namespace mlcppl;
using namespace std;

int main()
{
  
  pout<string>("Hello World - string");
  pout<const char*>("hello world - const char *");
  pout<int>(20);
  pout<const char>('a');
  pout<float>(43.043);
  
  vector<char> vc;
  vc = mlcppl::makevec<char> ({'a', 'b', 'c'});
  for (char x : vc)
    {
      pout<char> (x);
    }
  return 0;
}
