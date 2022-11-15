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
bool ReadCommands(istream &Strm, Set4LibInterfaces &LibList);

int main()
{
  Set4LibInterfaces LibList;
  istringstream iStrm;

  ExecPreprocesor("opis_dzialan.cmd", iStrm);  

  cout << iStrm.str() << endl;

  ReadCommands(iStrm, LibList);
}

bool ExecPreprocesor(const char * NazwaPliku, istringstream &IStrm4Cmds )
{
string Cmd4Preproc = "cpp -P ";
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

bool ReadCommands(istream &Strm, Set4LibInterfaces &LibList) 
{
  std::string cmdName;

  while (Strm >> cmdName) // sprawdza, czy w strumieniu jest jeszcze jakaś komenda
  {
    std::map <std::string, std::shared_ptr<LibInterface>>::iterator iter = LibList.FindLib(cmdName);
    if (iter == LibList.EndMap()) 
    {
      std::cerr << "Komenda " << cmdName << " nie została odnaleziona" << std::endl;
      return false;
    }
    // Tworzy komendę na podstawie funkcji wtyczki
    Interp4Command * pCommand = iter->second->pCreateCmd();
    if (!pCommand -> ReadParams(Strm)) 
    {
      std::cerr << "!!! Nieporawne parametry dla komendy '" << cmdName << std::endl;
      delete pCommand;
      return false;
    }
      cout << "Parametry:" << endl;
      pCommand -> PrintCmd();
      cout << endl;

      delete pCommand;
  }
  return true;
}