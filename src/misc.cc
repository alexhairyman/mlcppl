#include "misc.hh"

namespace mlcppl
{
  int cpl(char * c)
  {
    char ct;
    int i = 0;

    while (ct = *(c+i))
      {
        if (ct == '\0')
          {
            break;
          }
        else
          {
            i++;
          }
      }
    return i;
  }

  int cpl(const char * c)
  {
    char * ct = (char*) c;
    return cpl(ct);
  }
}
