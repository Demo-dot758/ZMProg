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
    public:
        Interp4Command *(*pCreateCmd)(void);
        LibInterface(std::string path);
        ~LibInterface();
        void * LibHandler;
        std::string CmdName;
};

#endif
