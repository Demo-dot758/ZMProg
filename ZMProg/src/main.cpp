#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <cstdio>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include "xmlinterp.hh"
#include "Configuration.hh"
#include "Sender.hh"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <list>

using namespace std;
using namespace xercesc;

#define LINE_SIZE 500


bool ExecPreprocesor(const char * NazwaPliku, istringstream &IStrm4Cmds );
bool ReadCommands(istream &Strm, Set4LibInterfaces &LibList,  Scene *ProgramScene);
bool ReadFile(const char* sFileName, Configuration &rConfig);
void SendScene(Scene *scene, Sender &sender);

int main()
{
  Set4LibInterfaces LibList;
  Configuration Config;
  ListOfLibs ConfigLibList;
  ListOfMobileObj MobileObjList;
  Scene *ProgramScene;
  Sender *ProgramSender;



  // Wczytywanie pliku XML
  if (!ReadFile("config/config.xml",Config))
  {
    cout << "Wczytywanie pliku konfiguracji config/config.xml nie powiodło się" << endl;
    return 1;
  }

  ConfigLibList = Config.GetLibList();
  for (int i = 0; i < ConfigLibList.size(); i++)
  {
    LibList.LoadLib(ConfigLibList.at(i));
  }

  MobileObjList = Config.GetObjList();

  // Scene ProgramScene;
  // for( auto i : MobileObjList)
  // {
  //   ProgramScene.AddMobileObject(i.first, i.second);
  // }
  ProgramScene = new Scene(MobileObjList);
  ProgramScene->Print();

  istringstream iStrm;
  // ExecPreprocesor("opis_dzialan.cmd", iStrm);  
  ReadCommands(iStrm, LibList, ProgramScene);

  ProgramScene->Print();

    cout << "Port: " << PORT << endl;
    int                 Socket4Sending;   

    if (!OpenConnection(Socket4Sending))
    {
      return 1;
    }
    
    Sender   ClientSender(Socket4Sending,ProgramScene);

    // const char *sConfigCmds =
    // "Clear\n"
    // "AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
    // "AddObj Name=Podstawa1.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
    // "AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n"       
    // "AddObj Name=Podstawa2 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(-1,-3,0)\n"
    // "AddObj Name=Podstawa2.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
    // "AddObj Name=Podstawa2.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";


    // cout << "Konfiguracja:" << endl;
    // cout << sConfigCmds << endl;
    
    SendScene(ProgramScene,ClientSender);
    ClientSender.Send("Close\n");
    ClientSender.CancelCountinueLooping();
    close(Socket4Sending);

//     cout << "Akcja:" << endl;    
//     for (GeomObject &rObj : Scn._Container4Objects) {
//       usleep(20000);
//       ChangeState(Scn);
//       Scn.MarkChange();
//       usleep(100000);
//     }
//     usleep(100000);

//     //-------------------------------------
//     // Należy pamiętać o zamknięciu połączenia.
//     // Bez tego serwer nie będzie reagował na
//     // nowe połączenia.
//     //
//     cout << "Close\n" << endl; // To tylko, aby pokazac wysylana instrukcje
//     Send(Socket4Sending,"Close\n");
//     ClientSender.CancelCountinueLooping();
//     Thread4Sending.join();
//     close(Socket4Sending);
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

bool ReadCommands(istream &Strm, Set4LibInterfaces &LibList, Scene *ProgramScene) 
{
  std::string cmdName, objName;

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
    objName = pCommand->GetObjName();
    // if (!ProgramScene->IfMobileObjectExists(objName))
    // {
    //   cerr << "Obiekt o nazwie '" << objName << "' nie istnieje" << endl;
    //   return false;
    // }
    auto object_ptr(ProgramScene->FindMobileObj(objName));
    cout << "Parametry "  << cmdName << ":" << endl;
    pCommand -> PrintCmd();
    // pCommand -> ReadParams(cmdName);
    cout << endl;

    delete pCommand;
  }
  return true;
}

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Configuration &rConfig)
{
  try 
  {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) 
  {
    char* message = XMLString::transcode(toCatch.getMessage());
    cerr << "Error during initialization! :\n";
    cerr << "Exception message is: \n"
          << message << "\n";
    XMLString::release(&message);
    return 1;
  }

  SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

  pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
  pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  pParser->setFeature(XMLUni::fgXercesDynamic, false);
  pParser->setFeature(XMLUni::fgXercesSchema, true);
  pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

  pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

  DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
  pParser->setContentHandler(pHandler);
  pParser->setErrorHandler(pHandler);

  try 
  {
    if (!pParser->loadGrammar("config/config.xsd", xercesc::Grammar::SchemaGrammarType,true)) 
    {
      cerr << "!!! Plik grammar/actions.xsd, '" << endl
          << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
          << endl;
      return false;
    }
    pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
    pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) 
  {
    char* sMessage = XMLString::transcode(Exception.getMessage());
    cerr << "Informacja o wyjatku: \n"
          << "   " << sMessage << "\n";
    XMLString::release(&sMessage);
    return false;
  }
  catch (const SAXParseException& Exception) 
  {
    char* sMessage = XMLString::transcode(Exception.getMessage());
    char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

    cerr << "Blad! " << endl
          << "    Plik:  " << sSystemId << endl
          << "   Linia: " << Exception.getLineNumber() << endl
          << " Kolumna: " << Exception.getColumnNumber() << endl
          << " Informacja: " << sMessage 
          << endl;

    XMLString::release(&sMessage);
    XMLString::release(&sSystemId);
    return false;
   }
  catch (...) 
  {
    cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
    return false;
  }

  delete pParser;
  delete pHandler;
  return true;
}

void SendScene(Scene *scene, Sender &sender)
{
  for (auto i : scene->GetMobileObjMap())
  {
    std::string msg = "AddObj ";
    msg += i.second->GetStateDesc();
    cout << "Msg: " << msg << endl;
    sender.Send(msg.c_str());
  }
}