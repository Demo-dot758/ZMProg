#include "LibInterface.hh"

LibInterface::LibInterface(std::string path)
{
    LibHandler = dlopen(path.c_str(),RTLD_LAZY);

    if (!LibHandler) 
    {
        std::cerr << "!!! Brak biblioteki: " << path << std::endl;
    }
    else
    {
        std::cout << "Znaleziono biblioteke: " << path <<std::endl;
    }

    void *pFun;
    pFun = dlsym(LibHandler,"CreateCmd");
    if (!pFun) 
    {
        std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
    }

    pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

    Interp4Command *pCmd = pCreateCmd();

    CmdName = pCmd->GetCmdName();
}

