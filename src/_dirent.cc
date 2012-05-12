/*
 * Author: @I_AUTH@
 * Version: @I_VER@
 * README: @I_READ@
 * Build Tool: CMAKE
 * File: _dirent.cc
 * 
 * This is a file built for easier use by me, but anyone can use it
 */

#include "_dirent.hh"

using namespace std;
using namespace mlcppl;

/*
const char* mlcppl::noreaderr::what() const throw()
{
  return "no read permissions";
}
*/

bool mlcppl::testreadsearch(string path)
{
  if (access(path.c_str(), R_OK | X_OK) == 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}

mlcppl::dirir::dirir(string path)
{
  try
    {

      if  (testreadsearch(path) == true)
        {
          cur_path = path;
        }
      else
        {
          throw norerr;
        }
    }
  catch (int i)
    {
      puts("ARGGGJHH");
    }
}

bool mlcppl::dirir::setdir(string path)
{
  try
    {
      if (testreadsearch(path) == true)
        {
          cur_path = path;
          return true;
        }
      else
        {
          throw norerr;
        }
    }
  catch(int i)
    {
      if(i = norerr)
        {
          puts("ARGGGHHHH");
        }
    }
}

vector<string> mlcppl::dirir::listfiles()
{
  vector<string> fls;
  diritr = opendir(cur_path.c_str());
  if (diritr != NULL)
    {
      while (dirlistr = readdir(diritr))
        {
          fls.insert(fls.begin(), dirlistr->d_name);
        }
      (void) closedir (diritr);
    }
  return fls;

}
