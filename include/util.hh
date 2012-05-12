/*
 * Author: @I_AUTH@
 * Version: @I_VER@
 * README: @I_READ@
 * Build Tool: CMAKE
 * File: util.hh
 */

#include <string>
#include <initializer_list>

using namespace std;

namespace mlcppl
{
	void _rm(string s);
	void rm(initializer_list<string> fls);
	
	void ls(string path);
	
	void _cp(string f, string t);
	void cp(initializer_list<string> fls);
	
	void _mv(string f, string t);
	void mv(initializer_list<string> fls);
}
