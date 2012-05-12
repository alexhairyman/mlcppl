#include "stdio.h"
#include <initializer_list>
#include <string>
#include "util.hh"

using namespace std;

namespace mlcppl
{
	void _rm(string s)
	{
		puts(s.c_str());
	}
	// Functions
	void rm(initializer_list<string> fls)
	{
		initializer_list<string>::iterator it;
		for(it = fls.begin();it != fls.end(); ++it)
		{
			string s(*it);
			_rm(s);
		}
	}
}

#ifdef _M_TEST
#include "stdio.h"
int main()
{
	mlcppl::rm({"alex","herrmann", "is a bamf"});
	return 0;
}
#endif
