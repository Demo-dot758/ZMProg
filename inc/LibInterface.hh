#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <iostream>

#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <cstdio>
#include "Interp4Command.hh"
#include "MobileObj.hh"

/*!
 * \file
 * \brief Definicja klasy LibInterface
 *
 * Plik zawiera definicję klasy LibInterface ...
 */

class LibInterface
{
    private:
        void * LibHandler;
        std::string CmdName;
    public:
        bool LoadLib(std::string path);
        Interp4Command *(*pCreateCmd)(void);
        LibInterface();
        ~LibInterface() {dlclose(LibHandler);}
};

#endif
