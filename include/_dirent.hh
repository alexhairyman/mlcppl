/*
 * Author: @I_AUTH@
 * Version: @I_VER@
 * README: @I_READ@
 * Build Tool: CMAKE
 * File: _dirent.hh
 * 
 * This is a file I wrote to simply help myself, but go ahead and use it
 */

#include "../conf.hh"
#include <dirent.h>
#include <vector>
#include <string>
#include <unistd.h>
#include <exception>
#include <stdio.h>

using namespace std;

namespace mlcppl
{
  static const int norerr = 10;
  /*
  class noreaderr : public exception
  {
  public:
    virtual const char* what() const throw();
  } nor;
  */

  bool testreadsearch(string path);

  class dirir
  {
  public:
    
    /*
     * sets the path, and creates the object
     *
     */
    dirir(string path);
    /*
     * if we have read permissions, returns true,
     * if not, well duh
     *
     */
    bool setdir(string path);
    
    /*
     * pretty self explanatory, vector with a list of files
     *
     */
    vector<string> listfiles();
    
  private:
    DIR *diritr;
    struct dirent *dirlistr;
    string cur_path;
  };
}
