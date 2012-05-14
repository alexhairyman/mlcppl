#include "util.hh"

using namespace mlcppl;

int main()
{
  pout<string>("Hello World - string");
  pout<const char*>("hello world - const char *");
  pout<int>(20);
  pout<float>(43.043);

  return 0;
}
