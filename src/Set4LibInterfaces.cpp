#include "Set4LibInterfaces.hh"


// Konstruktor
Set4LibInterfaces::Set4LibInterfaces(){
    LoadLib("libs/libInterp4Move.so");
    LoadLib("libs/libInterp4Set.so");
    LoadLib("libs/libInterp4Rotate.so");
    LoadLib("libs/libInterp4Pause.so");
}

void Set4LibInterfaces::LoadLib(std::string path){
    std::shared_ptr Libpointer = std::make_shared<LibInterface>(path);
    LibMap.insert({Libpointer->CmdName, Libpointer});
}