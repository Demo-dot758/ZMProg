#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <cstdio>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"

#define LINE_SIZE 500

using namespace std;


bool ExecPreprocesor(const char * NazwaPliku, istringstream &IStrm4Cmds );

int main()
{
  Set4LibInterfaces LibList;
}

bool ExecPreprocesor(const char * NazwaPliku, istringstream &IStrm4Cmds )
{
string Cmd4Preproc = "cpp -P";
char Line[LINE_SIZE];
ostringstream OTmpStrm;
Cmd4Preproc += NazwaPliku;
FILE* pProc = popen(Cmd4Preproc.c_str(),"r");

if (!pProc)
{
  return false;
}

while (fgets(Line,LINE_SIZE,pProc)) 
{
  OTmpStrm << Line;
}
IStrm4Cmds.str(OTmpStrm.str());

return pclose(pProc) == 0;
}