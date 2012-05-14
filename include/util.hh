#include "conf.hh"

using namespace std;

namespace mlcppl
{
  template<typename T> void pout(T p)
  {
    cout << p << '\n';
  }

  template<typename T> vector<T> makevec (initializer_list<T> initlist)
  {
    vector<T> vt;
    initializer_list<T>::iterator it;

    for(it=initlist.begin(); it != initlist.end(); ++it)
      {
        T s = *it;
        vt.insert(vt.end(), s);
      }
    return vt;
  }
}
