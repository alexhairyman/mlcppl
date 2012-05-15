#include "conf.hh"

using namespace std;

namespace mlcppl
{
  template<typename T> void pout(T p)
  {
    cout << p << '\n';
  }

  template<typename Tp> vector<Tp> makevec (initializer_list<Tp> initlist)
  {
    vector<Tp> vt;
    
    for(Tp x : initlist)
      {
        vt.insert(vt.end(), x); 
      }
    return vt;
  }
}
