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

    std::cout << std::endl;
    std::cout << pCmd->GetCmdName() << std::endl;
    std::cout << std::endl;
    pCmd->PrintSyntax();
    std::cout << std::endl;
    pCmd->PrintCmd();
    std::cout << std::endl;

    delete pCmd;
}