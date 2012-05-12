#include "_dirent.hh"
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;
using namespace mlcppl;

int main()
{
  dirir x ("/usr/bin");
  vector<string> l = x.listfiles();
  for (int i = 0; i < l.size(); i++)
    {
      puts(l.at(i).c_str());
    }
  return 0;  
}
